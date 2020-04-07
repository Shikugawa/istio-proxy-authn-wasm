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

#include <vector>
#include <memory>

#include <absl/strings/string_view.h>

#include "authentication/v1alpha1/policy.pb.h"
#include "envoy/config/filter/http/authn/v2alpha1/config.pb.h"

#include "envoy/config/core/v3/base.pb.h"

#include "istio/authn/context.pb.h"

#include "tls_certificate.h"
#include "proxy_wasm_intrinsics.h"

using RequestHeader = std::vector<std::pair<absl::string_view, absl::string_view>>;

namespace Envoy {
namespace Http {
namespace Istio {
namespace AuthN {

// FilterContext holds inputs, such as request dynamic metadata and connection
// and result data for authentication process.
class FilterContext {
 public:
  // TODO(shikugawa): metadata information insertion to FilterContext
  FilterContext(
      const RequestHeader& header_map,
      const istio::envoy::config::filter::http::authn::v2alpha1::FilterConfig&
          filter_config)
      : header_map_(header_map),
        filter_config_(filter_config) {
    // Check handled connection is tls or not by checking tls version. 
    // If we can retrieve tls version, handled connection is tls.
    std::string value;
    getValue({"connection", "tls_version"}, &value);
    is_tls_ = value != nullptr;
  }

  // Sets peer result based on authenticated payload. Input payload can be null,
  // which basically changes nothing.
  void setPeerResult(const istio::authn::Payload* payload);

  // Sets origin result based on authenticated payload. Input payload can be
  // null, which basically changes nothing.
  void setOriginResult(const istio::authn::Payload* payload);

  // Sets principal based on binding rule, and the existing peer and origin
  // result.
  void setPrincipal(
      const istio::authentication::v1alpha1::PrincipalBinding& binding);

  // Returns the authentication result.
  const istio::authn::Result& authenticationResult() { return result_; }

  // peer certificate info getter/setter
  const TlsPeerCertificateInfoPtr peerCertificateInfo() { return peer_cert_info_; }
  void setPeerCertificateInfo(const TlsPeerCertificateInfoPtr peer_cert_info) { peer_cert_info_ = peer_cert_info; }

  // local certificate info getter
  const TlsLocalCertificateInfoPtr localCertificateInfo() { return local_cert_info_; }
  void setLocalCertificateInfo(const TlsLocalCertificateInfoPtr peer_cert_info) { local_cert_info_ = local_cert_info; }

  // Accessor to the filter config
  const istio::envoy::config::filter::http::authn::v2alpha1::FilterConfig&
  filterConfig() const {
    return filter_config_;
  }

  // Gets JWT payload (output from JWT filter) for given issuer. If non-empty
  // payload found, returns true and set the output payload string. Otherwise,
  // returns false.
  bool getJwtPayload(const std::string& issuer, std::string* payload) const { return true; };

  const RequestHeader& headerMap() const { return header_map_; }

  bool isTls() { return is_tls_; }

 private:
  // TODO(shikugawa): JWT implementation, required metadata retrieval.
  // Helper function for getJwtPayload(). It gets the jwt payload from Envoy jwt
  // filter metadata and write to |payload|.
  bool getJwtPayloadFromEnvoyJwtFilter(const std::string& issuer,
                                       std::string* payload) const { return true; };
  // Helper function for getJwtPayload(). It gets the jwt payload from Istio jwt
  // filter metadata and write to |payload|.
  bool getJwtPayloadFromIstioJwtFilter(const std::string& issuer,
                                       std::string* payload) const { return true; };

  // Const reference to request info dynamic metadata. This provides data that
  // output from other filters, e.g JWT.
  const envoy::config::core::v3::Metadata& dynamic_metadata_;

  // Const reference to header map of the request. This provides request path
  // that could be used to decide if a JWT should be used for validation.
  const RequestHeader& header_map_;

  // Pointer to local certificate info on network connection of the request.
  const TlsLocalCertificateInfoPtr local_cert_info_;

  // Pointer to peer certificate info on network connection of the request.
  const TlsPeerCertificateInfoPtr peer_cert_info_;

  // Holds authentication attribute outputs.
  istio::authn::Result result_;

  // Store the Istio authn filter config.
  const istio::envoy::config::filter::http::authn::v2alpha1::FilterConfig&
      filter_config_;

  // whether handled connection is tls or not.
  bool is_tls_;
};

}  // namespace AuthN
}  // namespace Istio
}  // namespace Http
}  // namespace Envoy
