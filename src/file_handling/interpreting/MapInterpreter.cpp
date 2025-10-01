#include "MapInterpreter.h"
#include "../qf_types/QFTypes.h"
#include "../FileReader.h"

LevelLayer MapInterpreter::loadMapLayer(QFList* layer_contents) {
    LevelLayer layer;
    std::string layer_string;

    // Create layer from strings
    for (QFValue* value : layer_contents->getValues()) {
        try {
            layer.addRow(value->get<QFString>("Row is empty or not QFString!")->getValue());
        
        } catch (NullPointerException* e) {
            this->addException(e);
        
        } catch (LevelBuilderException* e) {
            this->addException(new InvalidMapLevelException(e->what(), value->getStartLine(), value->getEndLine()));
        }
    }
    return layer;
}

void MapInterpreter::loadChests(QFDict* level_contents, Level::LevelBuilder* level_builder) {
    QFList* chests;
    try {
        chests = level_contents->getValueFromKey("Chests")->get<QFList>("");
    
    // Levels do not require a chests list (only if chests are in the level)
    } catch (FileInterpreterException* e) {
        return;
    } catch (NoKeyFoundException* e) {
        return;
    }

    QFDict* chest_contents;
    int chest_pos[3];
    bool valid_chest;
    for (QFValue* chest : chests->getValues()) {
        valid_chest = true;
        try {
            chest_contents = chest->get<QFDict>("Chest contents are not QFDict!");
        } catch (FileInterpreterException* e) {
            this->addException(e);
            continue;
        }

        // Get chest position
        QFList* chest_pos_list;
        try {
            chest_pos_list = chest_contents->getValueFromKey("Position")->get<QFList>("Chest position is empty or not QFList!");
        
        } catch (FileInterpreterException* e) {
            this->addException(e);
            
        } catch (NoKeyFoundException* e) {
            this->addException(new InvalidMapLevelException(e->what(), chest_contents->getStartLine(), chest_contents->getEndLine()));
        }

        std::vector<QFValue*> values = chest_pos_list->getValues();

        if (values.size() != 3) {
            this->addException(new InvalidMapLevelException("Chest position needs three values!", 
                chest_pos_list->getStartLine(), chest_pos_list->getEndLine()));
        
        } else {
            for (int i=0; i<3; i++) {
                try {
                    chest_pos[i] = values.at(i)->get<QFInt>("Chest position values must be QFInt!")->getValue();
                } catch (FileInterpreterException* e) {
                    this->addException(e);
                } 
            }
        }
    }
}

Level* MapInterpreter::loadMapLevel(QFDict* level_contents) {
    // Initialisation of variables
    std::string level_string;
    Level::LevelBuilder level_builder = Level::LevelBuilder();

    // Get level name 
    try {
        std::string level_name = level_contents->getValueFromKey("Level Name")->get<QFString>("Level name is empty or not QFString!")->getValue();
        level_builder.setName(level_name);
    
    } catch (FileInterpreterException* e) {
        this->addException(e);
    
    } catch (NoKeyFoundException* e) {
        this->addException(new InvalidMapLevelException(e->what(), level_contents->getStartLine(), level_contents->getEndLine()));
    }

    // Get level layout
    QFList* layout;
    try {
        layout = level_contents->getValueFromKey("Layout")->get<QFList>("Layout is empty or not QFList!");
    
    } catch (FileInterpreterException* e) {
        throw e;
    
    } catch (NoKeyFoundException* e) {
        throw new InvalidMapLevelException(e->what(), 
            level_contents->getStartLine(), level_contents->getEndLine());
    }

    for (QFValue* layer : layout->getValues()) {
        try {
            level_builder.addLayer(this->loadMapLayer(layer->get<QFList>("Layer contents are empty or not QFList!")));
        } catch (FileInterpreterException* e) {
            this->addException(e);
        }
    }

    // Add chests
    this->loadChests(level_contents, &level_builder);

    // Build the level
    try {
        return level_builder.build();
    } catch (LevelBuilderException* e) {
        throw new InvalidMapLevelException(e->what(), level_contents->getStartLine(), level_contents->getEndLine());
    }
}

MapInterpreter::MapInterpreter(const std::string file_name, const std::string p) : 
    FileInterpreter::FileInterpreter(file_name), path(p.c_str()) {
    ;
}

int MapInterpreter::load(std::vector<Level*>* levels) {
    try {

        // Read File
        FileReader level_file_reader(path);
        QFDict level_file_contents(1);
        level_file_reader.readFile(&level_file_contents);

        // Get list of map levels
        QFList* map_levels_list;
        try {
            map_levels_list = level_file_contents.getValueFromKey("Map Levels")->get<QFList>("No QFList in a \"Map Levels\" key found.");
        
        } catch (FileInterpreterException* e) {
            this->addException(e);
            throw this->getExceptionList();
        
        } catch (NoKeyFoundException* e) {
            this->addException(new InvalidMapLevelException(e->what(), 
                level_file_contents.getStartLine(), level_file_contents.getEndLine()));
            throw this->getExceptionList(); 
        }

        std::vector<QFValue*> map_level_values = map_levels_list->getValues();

        for (QFValue* dict : map_level_values) {
            try {
                levels->push_back(this->loadMapLevel(dict->get<QFDict>("Entry in Map Levels list is not QFDict!")));
            } catch (FileInterpreterException* e) {
                this->addException(e);
            }
        }
        
        FileInterpreterExceptionList* exceptionList = this->getExceptionList();
        if (exceptionList->size() > 0) {
            throw exceptionList;
        }

        return (int)levels->size();
    
    } catch (FileInterpreterExceptionList* e) { 
        throw e;
    } catch (InvalidFileFormatException* e) {
        throw e;
    } catch (InvalidFileException* e) {
        throw e;
    }
} 