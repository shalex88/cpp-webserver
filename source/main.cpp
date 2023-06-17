#include <httplib.h>
#include <nlohmann/json.hpp>

int read_temperature() {
//    std::ifstream file("/sys/bus/w1/devices/w1_bus_master1/28-000008d34cd3/w1_slave");
//    std::string content;
//    std::getline(file, content); // Ignore first line
//    std::getline(file, content); // Read second line with temperature data
//    std::string temp_string = content.substr(content.find("t=") + 2);
//    float temp = std::stof(temp_string) / 1000; // Convert from milliCelsius to Celsius
    auto temp = -50 + (rand() % 101); // Random temperature between -50 and 50
    return temp;
}

int main() {
    httplib::Server svr;

    svr.Get("/data", [](const httplib::Request&, httplib::Response& res) {
        auto temp = read_temperature();
        nlohmann::json j;
        j["temperature"] = temp;
        res.set_content(j.dump(), "application/json");
    });

    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        std::ifstream file("../web/index.html");
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        res.set_content(content, "text/html");
    });

    svr.listen("0.0.0.0", 3000);

    return 0;
}