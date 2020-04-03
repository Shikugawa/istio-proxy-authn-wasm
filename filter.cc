/* Copyright 2019 Istio Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "filter.h"

#include "google/protobuf/text_format.h"
#include "google/protobuf/util/json_util.h"

#include "authentication/v1alpha1/policy.pb.h"

// #include "authn/peer_authenticator.h"

namespace Envoy {
namespace Extensions {
namespace Wasm {
namespace AuthnWasm {

bool AuthnRootContext::onConfigure(size_t) {
  logDebug("called AuthnRootContext::onConfigure()");

  WasmDataPtr configuration = getConfiguration();
  google::protobuf::util::JsonParseOptions json_options;
  google::protobuf::util::Status status = JsonStringToMessage(configuration->toString(),
                                      &filter_config_, json_options);

  if (status != google::protobuf::util::Status::OK) {
    logError("Cannot parse authentication filter config: " + configuration->toString());
    return false;
  }

  logDebug(configuration->toString());
  return true;
}

FilterHeadersStatus AuthnContext::onRequestHeaders(uint32_t) {
  WasmDataPtr header_pairs = getRequestHeaderPairs();
  auto header = header_pairs->pairs();
  const auto& config = filterConfig();
  for (const auto& method : config.policy().peers()) {
    switch (method.params_case()) {
      case istio::authentication::v1alpha1::PeerAuthenticationMethod::ParamsCase::kMtls:
        logDebug("peer authentication for mTLS:\n" + method.DebugString());
        break;
      case istio::authentication::v1alpha1::PeerAuthenticationMethod::ParamsCase::kJwt: 
        // TODO(shikugawa): should output deprecation message of Jwt method
        logDebug("peer authentication for JWT:\n" + method.DebugString());
        break;
      default:
        logDebug("unknown peer authentication:\n" + method.DebugString());
        break;
    }
  }
  return FilterHeadersStatus::Continue;
}

}
}
}
}