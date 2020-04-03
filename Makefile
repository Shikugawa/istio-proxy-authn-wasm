DOCKER_SDK=/sdk
CPP_API:=${DOCKER_SDK}
ABSL_API = /root/abseil-cpp

ABSL_SRCS = ${ABSL_API}/absl/strings/str_cat.cc ${ABSL_API}/absl/strings/str_split.cc ${ABSL_API}/absl/strings/numbers.cc ${ABSL_API}/absl/strings/ascii.cc
PROTO_SRCS = envoy/config/filter/http/authn/v2alpha1/config.pb.cc google/api/field_behavior.pb.cc authentication/v1alpha1/policy.pb.cc
# COMMON_SRCS = src/envoy/http/authn/filter_context.cc authenticator.cc

all: filter.wasm

%.wasm %.wat: %.cc ${CPP_API}/proxy_wasm_intrinsics.h ${CPP_API}/proxy_wasm_enums.h ${CPP_API}/proxy_wasm_externs.h ${CPP_API}/proxy_wasm_api.h ${CPP_API}/proxy_wasm_intrinsics.cc
	make istio-api-authentication-policy
	make istio-api-authn-config

	em++ -s STANDALONE_WASM=1 -s EMIT_EMSCRIPTEN_METADATA=1 -s EXPORTED_FUNCTIONS=['_malloc'] -s ERROR_ON_UNDEFINED_SYMBOLS=0 --std=c++17 -O3 \
	-I. \
	-I${CPP_API} \
	-I${ABSL_API} \
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
	protoc deps/api/envoy/config/filter/http/authn/v2alpha1/config.proto -Ideps/api -Ideps/googleapis --cpp_out=.

clear:
	rm -rf google authenticator envoy