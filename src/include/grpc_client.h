#pragma once

#include "string"

::grpc::Status SendHealthCheck(const std::string& addr);
