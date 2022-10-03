// Author: QPH-Coding
// Create: 2022/10/2
// File: http_request_head.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_HTTP_HTTP_REQUEST_HEAD_H_
#define QWEBSERVER_SRC_HTTP_HTTP_REQUEST_HEAD_H_

namespace HttpRequestHead {
using http_request_head = std::string;

const http_request_head Accept = "Accept";
const http_request_head AcceptCharset = "Accept-Charset";
const http_request_head AcceptEncoding = "Accept-Encoding";
const http_request_head AcceptLanguage = "Accept-Language";
const http_request_head AcceptDatetime = "Accept-Datetime";
const http_request_head Authorization = "Authorization";
const http_request_head CacheControl = "Cache-Control";
const http_request_head Connection = "Connection";
const http_request_head Cookie = "Cookie";
const http_request_head ContentLength = "Content-Length";
const http_request_head ContentMD5 = "Content-MD5";
const http_request_head ContentType = "Content-Type";
const http_request_head Date = "Date";
const http_request_head Expect = "Expect";
const http_request_head From = "From";
const http_request_head Host = "Host";
const http_request_head IfMatch = "If-Match";
const http_request_head IfModifiedSince = "If-Modified-Since";
const http_request_head IfNoneMatch = "If-None-Match";
const http_request_head IfRange = "If-Range";
const http_request_head IfUnmodifiedSince = "If-Unmodified-Since";
const http_request_head MaxForwards = "Max-Forwards";
const http_request_head Origin = "Origin";
const http_request_head Pragma = "Pragma";
const http_request_head ProxyAuthorization = "Proxy-Authorization";
const http_request_head Range = "Range";
const http_request_head Referer = "Referer";
const http_request_head TE = "TE";
const http_request_head UserAgent = "User-Agent";
const http_request_head Upgrade = "Upgrade";
const http_request_head Via = "Via";
const http_request_head Warning = "Warning";
}
#endif //QWEBSERVER_SRC_HTTP_HTTP_REQUEST_HEAD_H_
