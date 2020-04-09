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

#include "tls_certificate.h"
#include "proxy_wasm_intrinsics.h"

namespace Envoy {
namespace Http {
namespace Istio {
namespace AuthN {

constexpr absl::string_view Connection = "connection";
constexpr absl::string_view TlsVersion = "tls_version";
constexpr absl::string_view UriSanPeerCertificate = "uri_san_peer_certificate";
constexpr absl::string_view LocalSanPeerCertificate = "uri_san_local_certificate";
constexpr absl::string_view Mtls = "mtls";

class ConnectionContext {
public:
  ConnectionContext() {
    if (isTls()) {
      peer_cert_info_ = std::make_unique<TlsPeerCertificateInfo>();
      peer_cert_info_->uriSans() = getProperty({Connection, UriSanPeerCertificate}).value_or("");
      local_cert_info_ = std::make_unique<TlsLocalCertificateInfo>();
      local_cert_info_->uriSans() = getProperty({Connection, UriSanLocalCertificate}).value_or("");
      mtls_ = getProperty({Connection, Mtls}).value_or(false); 
    }
  }
  bool isMtls() { return mtls_; }
  bool isTls() { return getProperty({Connection, TlsVersion}).has_value(); }

private:
  std::unique_ptr<TlsPeerCertificateInfo> peer_cert_info_;
  std::unique_ptr<LocalPeerCertificateInfo> local_cert_info_;
  bool mtls_;
};

}  // namespace AuthN
}  // namespace Istio
}  // namespace Http
}  // namespace Envoy
