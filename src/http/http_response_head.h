// Author: QPH-Coding
// Create: 2022/10/2
// File: http_response_head.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_HTTP_HTTP_RESPONSE_HEAD_H_
#define QWEBSERVER_SRC_HTTP_HTTP_RESPONSE_HEAD_H_

namespace HttpResponseHead {
using http_response_head = std::string;

const http_response_head AccessControlAllowOrigin = "Access-Control-Allow-Origin";
const http_response_head AcceptPatch = "Accept-Patch";
const http_response_head AcceptRanges = "Accept-Ranges";
const http_response_head Age = "Age";
const http_response_head Allow = "Allow";
const http_response_head CacheControl = "Cache-Control";
const http_response_head Connection = "Connection";
const http_response_head ContentDisposition = "Content-Disposition";
const http_response_head ContentEncoding = "Content-Encoding";
const http_response_head ContentLanguage = "Content-Language";
const http_response_head ContentLength = "Content-Length";
const http_response_head ContentLocation = "Content-Location";
const http_response_head ContentMD5 = "Content-MD5";
const http_response_head ContentRange = "Content-Range";
const http_response_head ContentType = "Content-Type";
const http_response_head Date = "Date";
const http_response_head ETag = "ETag";
const http_response_head Expires = "Expires";
const http_response_head KeepAlive = "Keep-Alive";
const http_response_head LastModified = "Last-Modified";
const http_response_head Link = "Link";
const http_response_head Location = "Location";
const http_response_head P3P = "P3P";
const http_response_head Pragma = "Pragma";
const http_response_head ProxyAuthenticate = "Proxy-Authenticate";
const http_response_head PublicKeyPins = "Public-Key-Pins";
const http_response_head Refresh = "Refresh";
const http_response_head RetryAfter = "Retry-After";
const http_response_head Server = "Server";
const http_response_head SetCookie = "Set-Cookie";
const http_response_head Status = "Status";
const http_response_head Trailer = "Trailer";
const http_response_head TransferEncoding = "Transfer-Encoding";
const http_response_head Upgrade = "Upgrade";
const http_response_head Vary = "Vary";
const http_response_head Via = "Via";
const http_response_head Warning = "Warning";
const http_response_head WWWAuthenticate = "WWW-Authenticate";
}

#endif //QWEBSERVER_SRC_HTTP_HTTP_RESPONSE_HEAD_H_
