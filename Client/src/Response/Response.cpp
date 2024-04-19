#include "Response/Response.hpp"

Response::Response(const std::string& json) {
    nlohmann::json response = nlohmann::json::parse(json);

    deleted = bool(int(response["deleted"]));
    file = response["file"];
    new_file_name = response["new_file_name"];

    changes = response.at("changes").get<std::unordered_map<std::string, std::string>>();
}
