/* Copyright 2020 Istio Authors. All Rights Reserved.
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

#pragma once

#include <memory>
#include <absl/strings/string_view.h>

#include "proxy_wasm_intrinsics.h"

namespace Envoy {
namespace Http {
namespace Istio {
namespace AuthN {

using HeaderMapPairs = std::vector<std::pair<absl::string_view, absl::string_view>>;

class HttpContext {
public:
  void onRequestHeaders() {
    header_ = getRequestHeader()->pairs();
  }

  void onRequesTrailers() {
    header_ = getRequestTrailer()->pairs();
  }

private:
  HeaderMapPairs header_;
  HeaderMapPairs trailer_;
};

}  // namespace AuthN
}  // namespace Istio
}  // namespace Http
}  // namespace Envoy
