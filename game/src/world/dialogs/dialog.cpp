#include "dialog.hpp"

// ------------------------------------------------------------------------------------------------

Dialog::Dialog(std::string file_name)
{
    std::string data_file_path = "game/data/npcs/dialogs/" + file_name + ".json";

    // Extract the data ---------------------------------------------------------------------------

    std::ifstream json_file_unparsed(data_file_path.c_str());

    if (!json_file_unparsed.is_open())
    {
        std::cerr << "Error opening input file." << std::endl;
        exit(-1);
    }
    nlohmann::json json_file = nlohmann::json::parse(json_file_unparsed);
    json_file_unparsed.close();

    std::string npc_name = json_file["npc_name"];
    std::string sprite_path = json_file["sprite_path"];
    std::vector<int> coordinates = json_file["coordinates"];
    int speed = json_file["speed"];
    int SheetType = json_file["sprite_sheet_type"];
}
Dialog::~Dialog()
{
}

// ------------------------------------------------------------------------------------------------