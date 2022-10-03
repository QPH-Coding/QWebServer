// Author: QPH-Coding
// Create: 2022/10/2
// File: http_response_status.h
// License: Apache 2.0

#ifndef QWEBSERVER_SRC_HTTP_HTTP_RESPONSE_STATUS_H_
#define QWEBSERVER_SRC_HTTP_HTTP_RESPONSE_STATUS_H_
#include <string>

namespace HttpResponseStatus {
using http_response_status = std::pair<int, std::string>;
const http_response_status Continue(101, "Continue");
const http_response_status SwitchingProtocols(102, "Switching Protocols");

const http_response_status OK(200, "OK");
const http_response_status Created(201, "Created");
const http_response_status Accepted(202, "Accepted");
const http_response_status NonAuthoritativeInformation(203, "Non-Authoritative Information");
const http_response_status NoContent(204, "No Content");
const http_response_status ResetContent(205, "Reset Content");
const http_response_status PartialContent(206, "Partial Content");

const http_response_status MultipleChoices(300, "Multiple Choices");
const http_response_status MovedPermanently(301, "Moved Permanently");
const http_response_status Found(302, "Found");
const http_response_status SeeOther(304, "See Other");
const http_response_status NotModified(305, "Not Modified");
const http_response_status UseProxy(306, "Use Proxy");
const http_response_status Unused(307, "Unused");
const http_response_status TemporaryRedirect(308, "Temporary Redirect");

const http_response_status BadRequest(400, "Bad Request");
const http_response_status Unauthorized(401, "Unauthorized");
const http_response_status PaymentRequired(402, "Payment Required");
const http_response_status Forbidden(403, "Forbidden");
const http_response_status NotFound(404, "Not Found");
const http_response_status MethodNotAllowed(405, "Method Not Allowed");
const http_response_status NotAcceptable(406, "Not Acceptable");
const http_response_status ProxyAuthenticationRequired(407, "Proxy Authentication Required");
const http_response_status RequestTimeout(408, "Request Time-out");
const http_response_status Conflict(409, "Conflict");
const http_response_status Gone(410, "Gone");
const http_response_status LengthRequired(411, "Length Required");
const http_response_status PreconditionFailed(412, "Precondition Failed");
const http_response_status RequestEntityTooLarge(413, "Request Entity Too Large");
const http_response_status RequestUriTooLarge(414, "Request-URI Too Large");
const http_response_status UnsupportedMediaType(415, "Unsupported Media Type");
const http_response_status RequestedRangeNotSatisfiable(416, "Requested range not satisfiable");
const http_response_status ExpectationFailed(417, "Expectation Failed");

const http_response_status InternalServerError(500, "Internal Server Error");
const http_response_status NotImplemented(501, "Not Implemented");
const http_response_status BadGateway(502, "Bad Gateway");
const http_response_status ServiceUnavailable(503, "Service Unavailable");
const http_response_status GatewayTimeOut(504, "Gateway Time-out");
const http_response_status HTTPVersionNotSupported(505, "HTTP Version not supported");
}
#endif //QWEBSERVER_SRC_HTTP_HTTP_RESPONSE_STATUS_H_
