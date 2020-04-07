DOCKER_SDK=/sdk

CPP_API:=${DOCKER_SDK}
ABSL_API = /root/abseil-cpp
ENVOY_API = deps/envoy/source
UDPA_API = deps/udpa

ENVOY_TYPE_V3_API = deps/envoy/api/envoy/type/v3
ENVOY_CONFIG_CORE_V3_API = deps/envoy/api/envoy/config/core/v3

ABSL_SRCS = ${ABSL_API}/absl/strings/str_cat.cc ${ABSL_API}/absl/strings/str_split.cc ${ABSL_API}/absl/strings/numbers.cc ${ABSL_API}/absl/strings/ascii.cc
PROTO_SRCS = envoy/config/filter/http/authn/v2alpha1/config.pb.cc google/api/field_behavior.pb.cc authentication/v1alpha1/policy.pb.cc

all: filter.wasm

%.wasm %.wat: %.cc ${CPP_API}/proxy_wasm_intrinsics.h ${CPP_API}/proxy_wasm_enums.h ${CPP_API}/proxy_wasm_externs.h ${CPP_API}/proxy_wasm_api.h ${CPP_API}/proxy_wasm_intrinsics.cc
	make istio-api-authentication-policy
	make istio-api-authn-config
	make build-protoc-gen-validate-validate
	make build-envoy-config-core-v3-base
	make build-context

	em++ -s STANDALONE_WASM=1 -s EMIT_EMSCRIPTEN_METADATA=1 -s EXPORTED_FUNCTIONS=['_malloc'] -s ERROR_ON_UNDEFINED_SYMBOLS=0 --std=c++17 -O3 \
	-I. \
	-I${CPP_API} \
	-I${ABSL_API} \
	-I${ENVOY_API} \
	-I${CPP_API}/google/protobuf \
	-I/usr/local/include \
	$*.cc \
	${CPP_API}/proxy_wasm_intrinsics.pb.cc \
	${CPP_API}/proxy_wasm_intrinsics.cc \
	${ABSL_SRCS} \
	${PROTO_SRCS} \
	${CPP_API}/libprotobuf.a \
	-o $*.wasm

	make clear

istio-api-authentication-policy:
	protoc deps/googleapis/google/api/field_behavior.proto -Ideps/googleapis --cpp_out=.
	protoc deps/api/authentication/v1alpha1/policy.proto -Ideps/googleapis -Ideps/api --cpp_out=.
	
istio-api-authn-config:
	protoc deps/api/envoy/config/filter/http/authn/v2alpha1/config.proto \
	-Ideps/api \
	-Ideps/googleapis \
	--cpp_out=.

build-context:
	protoc istio/authn/context.proto --cpp_out=.

build-protoc-gen-validate-validate:
	mkdir -p ${PROTOC_GEN_VALIDATE_API} && \
	protoc deps/protoc-gen-validate/validate/validate.proto --cpp_out=. && \
	mv deps/protoc-gen-validate/validate/validate.pb.h ${PROTOC_GEN_VALIDATE_API} && \
 	mv deps/protoc-gen-validate/validate/validate.pb.cc ${PROTOC_GEN_VALIDATE_API}

build-envoy-config-core-v3-base:
	protoc ${UDPA_API}/udpa/annotations/versioning.proto -I${UDPA_API} --cpp_out=.
	protoc ${UDPA_API}/udpa/annotations/status.proto -I${UDPA_API} --cpp_out=.
	protoc \
		${ENVOY_TYPE_V3_API}/semantic_version.proto \
		${ENVOY_TYPE_V3_API}/percent.proto \
		${ENVOY_CONFIG_CORE_V3_API}/http_uri.proto \
		${ENVOY_CONFIG_CORE_V3_API}/backoff.proto \
		${ENVOY_CONFIG_CORE_V3_API}/socket_option.proto \
		${ENVOY_CONFIG_CORE_V3_API}/address.proto \
		${ENVOY_CONFIG_CORE_V3_API}/base.proto \
	-Ideps/envoy/api \
	-I/usr/local/include \
	-Ideps/udpa \
	-Ideps/protoc-gen-validate \
	--cpp_out=.

clear:
	rm -rf google authentication envoy udpa validate annotations istio/authn/*.pb.h istio/authn/*.pb.cc