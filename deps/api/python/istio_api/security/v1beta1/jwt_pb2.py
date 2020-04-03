# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: security/v1beta1/jwt.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from google.api import field_behavior_pb2 as google_dot_api_dot_field__behavior__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='security/v1beta1/jwt.proto',
  package='istio.security.v1beta1',
  syntax='proto3',
  serialized_options=_b('Z\035istio.io/api/security/v1beta1'),
  serialized_pb=_b('\n\x1asecurity/v1beta1/jwt.proto\x12\x16istio.security.v1beta1\x1a\x1fgoogle/api/field_behavior.proto\"\xe1\x01\n\x07JWTRule\x12\x13\n\x06issuer\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12\x11\n\taudiences\x18\x02 \x03(\t\x12\x10\n\x08jwks_uri\x18\x03 \x01(\t\x12\x0c\n\x04jwks\x18\n \x01(\t\x12\x37\n\x0c\x66rom_headers\x18\x06 \x03(\x0b\x32!.istio.security.v1beta1.JWTHeader\x12\x13\n\x0b\x66rom_params\x18\x07 \x03(\t\x12 \n\x18output_payload_to_header\x18\x08 \x01(\t\x12\x1e\n\x16\x66orward_original_token\x18\t \x01(\x08\".\n\tJWTHeader\x12\x11\n\x04name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12\x0e\n\x06prefix\x18\x02 \x01(\tB\x1fZ\x1distio.io/api/security/v1beta1b\x06proto3')
  ,
  dependencies=[google_dot_api_dot_field__behavior__pb2.DESCRIPTOR,])




_JWTRULE = _descriptor.Descriptor(
  name='JWTRule',
  full_name='istio.security.v1beta1.JWTRule',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='issuer', full_name='istio.security.v1beta1.JWTRule.issuer', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=_b('\340A\002'), file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='audiences', full_name='istio.security.v1beta1.JWTRule.audiences', index=1,
      number=2, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='jwks_uri', full_name='istio.security.v1beta1.JWTRule.jwks_uri', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='jwks', full_name='istio.security.v1beta1.JWTRule.jwks', index=3,
      number=10, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='from_headers', full_name='istio.security.v1beta1.JWTRule.from_headers', index=4,
      number=6, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='from_params', full_name='istio.security.v1beta1.JWTRule.from_params', index=5,
      number=7, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='output_payload_to_header', full_name='istio.security.v1beta1.JWTRule.output_payload_to_header', index=6,
      number=8, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='forward_original_token', full_name='istio.security.v1beta1.JWTRule.forward_original_token', index=7,
      number=9, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=88,
  serialized_end=313,
)


_JWTHEADER = _descriptor.Descriptor(
  name='JWTHeader',
  full_name='istio.security.v1beta1.JWTHeader',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='istio.security.v1beta1.JWTHeader.name', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=_b('\340A\002'), file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='prefix', full_name='istio.security.v1beta1.JWTHeader.prefix', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=315,
  serialized_end=361,
)

_JWTRULE.fields_by_name['from_headers'].message_type = _JWTHEADER
DESCRIPTOR.message_types_by_name['JWTRule'] = _JWTRULE
DESCRIPTOR.message_types_by_name['JWTHeader'] = _JWTHEADER
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

JWTRule = _reflection.GeneratedProtocolMessageType('JWTRule', (_message.Message,), {
  'DESCRIPTOR' : _JWTRULE,
  '__module__' : 'security.v1beta1.jwt_pb2'
  # @@protoc_insertion_point(class_scope:istio.security.v1beta1.JWTRule)
  })
_sym_db.RegisterMessage(JWTRule)

JWTHeader = _reflection.GeneratedProtocolMessageType('JWTHeader', (_message.Message,), {
  'DESCRIPTOR' : _JWTHEADER,
  '__module__' : 'security.v1beta1.jwt_pb2'
  # @@protoc_insertion_point(class_scope:istio.security.v1beta1.JWTHeader)
  })
_sym_db.RegisterMessage(JWTHeader)


DESCRIPTOR._options = None
_JWTRULE.fields_by_name['issuer']._options = None
_JWTHEADER.fields_by_name['name']._options = None
# @@protoc_insertion_point(module_scope)
