#include "logger.hpp"

logging::logger< logging::file_log_policy > log_inst( "00Casper.log" ,
                                                      logging::severity_type::debug1);
