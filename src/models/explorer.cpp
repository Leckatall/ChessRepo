//
// Created by Lecka on 04/03/2025.
//


// #include "explorer.h"
//
// #include <chess.hpp>
// #include <cpr/cpr.h>
// #include <nlohmann/json.hpp>
//
// using json = nlohmann::json;
//
// chess::Movelist Explorer::getMoves(std::string FEN) {
//
//     cpr::Response r = cpr::Get(cpr::Url{"https://explorer.lichess.ovh/lichess"});
//     std::cout << "Status code: " << r.status_code << std::endl;
//     if(r.status_code == 200) {
//         json j = json::parse(r.text);
//         std::cout << "Response body: " << j << std::endl;
//     }
//     return {};
// }

