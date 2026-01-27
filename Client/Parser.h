#pragma once

std::unordered_map<std::string, std::function<void(const nlohmann::json&)>> parsers;

void addEnemyAttack(const nlohmann::json& enemyStep)
{
    std::cout << enemyStep["enemyName"].get<std::string>()
        + ConvertCP1251ToUTF8(" сказал: ")
        + enemyStep["replic"].get<std::string>()
        + "\n";

    if (enemyStep["hasArmor"].get<bool>() == true)
    {
        std::cout << enemyStep["enemyName"].get<std::string>()
            + ConvertCP1251ToUTF8(" ударил вас на ")
            + std::to_string(enemyStep["loseHealth"].get<int>())
            + ConvertCP1251ToUTF8(" урона и снёс вам ")
            + std::to_string(enemyStep["loseArmor"].get<int>())
            + ConvertCP1251ToUTF8(" единиц брони.\n");
        std::cout << ConvertCP1251ToUTF8("Ваше здоровье: ")
            + std::to_string(enemyStep["currentHealth"].get<int>())
            + "\n";
        std::cout << ConvertCP1251ToUTF8("Ваша броня: ")
            + std::to_string(enemyStep["currentArmor"].get<int>())
            + "\n";
    }
    else
    {
        std::cout << enemyStep["enemyName"].get<std::string>()
            + ConvertCP1251ToUTF8(" ударил вас на ")
            + std::to_string(enemyStep["loseHealth"].get<int>())
            + ConvertCP1251ToUTF8(" урона.\n");
        std::cout << ConvertCP1251ToUTF8("Ваше здоровье: ")
            + std::to_string(enemyStep["currentHealth"].get<int>())
            + "\n";
        std::cout << ConvertCP1251ToUTF8("Ваша броня: ")
            + std::to_string(enemyStep["currentArmor"].get<int>())
            + "\n";
    }
}

void addPlayerDeath(const nlohmann::json& obj)
{
    if (obj["isDead"].get<bool>() != true)
    {
        return; // ConvertCP1251ToUTF8
    }

    std::cout << ConvertCP1251ToUTF8("Вы умерли, ваши вещи остались в комнате [")
        + std::to_string(obj["x"].get<int>())
        + ConvertCP1251ToUTF8(", ")
        + std::to_string(obj["y"].get<int>())
        + ConvertCP1251ToUTF8("] на ")
        + std::to_string(obj["Floor"].get<int>())
        + ConvertCP1251ToUTF8(" этаже\n");
}

void addLevelUp(const nlohmann::json& obj)
{
    if (obj["isLevelUp"].get<bool>() == false)
    {
        return;
    }

    std::cout << ConvertCP1251ToUTF8("Вы получили новый уровень: ")
        + std::to_string(obj["newLevel"].get<int>())
        + "\n";

    std::cout << ConvertCP1251ToUTF8("Опыта до следующего уровня: ")
        + std::to_string(obj["nextLevelExp"].get<int>())
        + "\n";

    std::cout << ConvertCP1251ToUTF8("Текущий опыт: ")
        + std::to_string(obj["currentExp"].get<int>())
        + "\n";
}

void initFillANSWER()
{
    bool parsersInitialized = false; // сУрЭкУсИй 

    if (parsersInitialized) // короче чтобы не было повторного вызова а то будет badlock :D
        return;

    // я
    parsers["Me"] = [](const nlohmann::json& obj)
        {
            std::cout << ConvertCP1251ToUTF8("\nИмя: ")
                + obj["content"]["username"].get<std::string>()
                + ConvertCP1251ToUTF8("\nУровень: ")
                + std::to_string(obj["content"]["level"].get<int>())
                + ConvertCP1251ToUTF8("\nТекущий опыт: ")
                + std::to_string(obj["content"]["exp"].get<int>())
                + ConvertCP1251ToUTF8("\nОпыта до следующего уровня: ")
                + std::to_string(obj["content"]["expToLU"].get<int>())
                + ConvertCP1251ToUTF8("\nВместимость инвентаря: ")
                + std::to_string(obj["content"]["maxInventory"].get<int>())
                + ConvertCP1251ToUTF8("\nЗдоровье: ")
                + std::to_string(obj["content"]["health"].get<int>())
                + ConvertCP1251ToUTF8("\nБроня: ")
                + std::to_string(obj["content"]["armor"].get<int>())
                + ConvertCP1251ToUTF8("\nНавык владения оружием: ")
                + std::to_string(obj["content"]["weaponSkill"].get<int>())
                + "\n";

            if (obj["content"]["currentWeapon"] != "")
            {
                std::cout << ConvertCP1251ToUTF8("Текущее оружие: ")
                    + obj["content"]["currentWeapon"].get<std::string>()
                    + "\n";
            }
        };

    // осмореться 
    parsers["Look"] = [](const nlohmann::json& obj)
        {
            size_t c = 1;
            std::cout << ConvertCP1251ToUTF8("\n---------------------\n");

            std::cout << obj["content"]["locationName"].get<std::string>()
                + ConvertCP1251ToUTF8(": Этаж ")
                + std::to_string(obj["content"]["coordinates"]["floor"].get<int>())
                + ConvertCP1251ToUTF8("\n");

            std::cout << ConvertCP1251ToUTF8("Координаты: [")
                + std::to_string(obj["content"]["coordinates"]["x"].get<int>())
                + ConvertCP1251ToUTF8(", ")
                + std::to_string(obj["content"]["coordinates"]["y"].get<int>())
                + ConvertCP1251ToUTF8("]\n");

            //Пустая затычка v
            // logs.push_back(ftxui::text("")); уже нет :P
            //Пустая затычка ^

            std::cout << ConvertCP1251ToUTF8("\n=== ОПИСАНИЕ ===\n");

            std::cout << obj["content"]["locationDescription"].get<std::string>()
                + ConvertCP1251ToUTF8("\n");

            //Предметы и враги

            std::vector<nlohmann::json> items = obj["content"]["items"].get<nlohmann::json>();

            if (!items.empty())
            {
                std::cout << ConvertCP1251ToUTF8("\n=== ПРЕДМЕТЫ ===\n");

                c = 1;

                for (auto it : items)
                {
                    std::cout << std::to_string(c)
                        + ". " + it["description"].get<std::string>()
                        + "\n";
                    ++c;
                }
            }

            std::vector<nlohmann::json> enemies = obj["content"]["enemies"].get<nlohmann::json>();

            if (!enemies.empty())
            {
                std::cout << ConvertCP1251ToUTF8("\n=== ВРАГИ ===\n");

                c = 1;

                for (auto it : enemies)
                {
                    std::cout << std::to_string(c)
                        + ". " + it["description"].get<std::string>()
                        + "\n";
                    ++c;
                }

                //logs.push_back(ftxui::vbox(enms) | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 50));
            }

            //Направления

            std::vector<std::string> sides = obj["content"]["sides"].get<std::vector<std::string>>();
            std::string sidesAll;

            for (auto it : sides)
            {
                sidesAll += it + " ";
            }

            if (!sides.empty())
            {
                std::cout << ConvertCP1251ToUTF8("\nВы можете пойти на ")
                    + sidesAll
                    + "\n";
            }

            //Этажи

            if (obj["content"]["coordinates"]["canGoUp"].get<bool>() == true)
            {
                std::cout << ConvertCP1251ToUTF8("Из этой локации вы можете подняться на этаж выше\n");
            }

            if (obj["content"]["coordinates"]["canGoDown"].get<bool>() == true)
            {
                std::cout << ConvertCP1251ToUTF8("Из этой локации вы можете опуститься на этаж ниже\n");
            }

            if (obj["content"]["coordinates"]["isExitBroken"].get<bool>() == true)
            {
                std::cout << ConvertCP1251ToUTF8("На локации сломан лифт, вы не можете перейти на другой этаж пока не почините лифт\n");
            }
        };

    // восток, север, запад, юг и т.д
    parsers["Move"] = [](const nlohmann::json& obj)
        {
            if (obj["content"]["canMove"].get<bool>() == false)
            {
                std::cout << ConvertCP1251ToUTF8("Вы не можете пойти в эту сторону!\n");
                return;
            }
            if (obj["content"]["unknownSide"].get<bool>() == true)
            {
                std::cout << ConvertCP1251ToUTF8("Неизвестная сторона!\n");
                return;
            }

            if (obj["content"]["moved"].get<bool>() == true)
            {
                std::cout << ConvertCP1251ToUTF8("Вы переместились!\n");
            }
            else
            {
                return;
            }

            nlohmann::json lookObj = obj["content"]["look"].get<nlohmann::json>();
            if (!lookObj.empty())
            {
                parsers["Look"](lookObj);
            }
        };

    // пИкап не мастер а подобрать :<
    parsers["Pickup"] = [](const nlohmann::json& obj)
        {
            if (obj["content"]["canPickup"].get<bool>() == false)
            {
                std::cout << ConvertCP1251ToUTF8("Вы не можете подбирать предметы пока в комнате есть враги!\n");
            }
            else
            {
                if (obj["content"]["isInventoryFull"].get<bool>() == true)
                {
                    std::cout << ConvertCP1251ToUTF8("Ваш инвентарь полон!\n");
                }
                else
                {
                    if (obj["content"]["pickuped"].get<bool>() == true)
                    {
                        std::cout << ConvertCP1251ToUTF8("Вы подобрали ")
                            + obj["content"]["item"].get<std::string>()
                            + "\n";
                    }
                    else
                    {
                        std::cout << ConvertCP1251ToUTF8("Этого предмета нет в комнате\n");
                    }
                }
            }
        };

    // выбросить, наверное камни в автора :D (Но это не точно...)
    parsers["Drop"] = [](const nlohmann::json& obj)
        {
            if (obj["content"]["itemFound"] == false)
            {
                std::cout << ConvertCP1251ToUTF8("У вас нет этого предмета\n");
            }
            else
            {
                std::cout << ConvertCP1251ToUTF8("Вы выбросили ")
                    + obj["content"]["dropped"].get<std::string>()
                    + "\n";
            }
        };

    // Вот знаешь когда у тебя дарка в кормане ? Надо проверить есть ли ещё че инвентарь
    parsers["Inventory"] = [](const nlohmann::json& obj)
        {
            std::cout << ConvertCP1251ToUTF8("Инвентарь: \n");

            std::vector<std::string> invItems = obj["content"]["items"].get<std::vector<std::string>>();
            int c = 1;
            for (auto it : invItems)
            {
                std::cout << std::to_string(c) + ". " + it + "\n"; // я ебал. А кого ? 
                ++c;
            }
        };

    // Вот смотри есть дырка
    parsers["LookItem"] = [](const nlohmann::json& obj)
        {
            if (obj["content"]["found"].get<bool>() == true)
            {
                nlohmann::json obbj = obj["content"]["object"].get<nlohmann::json>();

                if (!obbj.empty())
                {
                    if (obbj["type"] == "Item")
                    {
                        std::cout << ConvertCP1251ToUTF8("Предмет: ")
                            + obbj["name"].get<std::string>()
                            + "\n";

                        std::cout << ConvertCP1251ToUTF8("Описание: ")
                            + obbj["description"].get<std::string>()
                            + "\n";

                        if (obbj["ItemType"] == "Component")
                        {
                            std::cout << ConvertCP1251ToUTF8("Нельзя использовать\n"); // ав ну-ка подшкаонку 

                            return;
                        }
                        if (obbj["ItemType"] == "Weapon")
                        {
                            std::cout << ConvertCP1251ToUTF8("Урон: ") // урод
                                + std::to_string(obbj["damage"].get<int>())
                                + "\n";

                            std::cout << ConvertCP1251ToUTF8("Вы можете экипировать и атаковать этот предметом\n");

                            return;
                        }
                        if (obbj["ItemType"] == "Armor")
                        {
                            std::cout << ConvertCP1251ToUTF8("Броня: ")
                                + std::to_string(obbj["armor"].get<int>())
                                + "\n";

                            std::cout << ConvertCP1251ToUTF8("Вы можете использовать этот предмет\n");

                            return;
                        }
                        if (obbj["ItemType"] == "Heal")
                        {
                            std::cout << ConvertCP1251ToUTF8("Здоровье: ")
                                + std::to_string(obbj["heal"].get<int>())
                                + "\n";

                            std::cout << ConvertCP1251ToUTF8("Вы можете использовать этот предмет\n");

                            return;
                        }
                    }
                    if (obbj["type"] == "Enemy")
                    {
                        std::cout << ConvertCP1251ToUTF8("Враг: ")
                            + obbj["name"].get<std::string>()
                            + "\n";

                        std::cout << ConvertCP1251ToUTF8("Описание: ")
                            + obbj["description"].get<std::string>()
                            + "\n";

                        std::cout << ConvertCP1251ToUTF8("Здоровье: ")
                            + std::to_string(obbj["health"].get<int>())
                            + "\n";

                        std::cout << ConvertCP1251ToUTF8("Урон: ")
                            + std::to_string(obbj["damage"].get<int>())
                            + "\n";
                    }
                    return;
                }
            }
            else
            {
                std::cout << ConvertCP1251ToUTF8("У вас не такого предмета или такого врага нет в комнате!\n");
            }
        };

    // юЗиТеМ 
    parsers["UseItem"] = [](const nlohmann::json& obj)
        {
            if (obj["content"]["haveItem"] == true)
            {
                nlohmann::json itmm = obj["content"]["item"].get<nlohmann::json>();
                if (!itmm.empty())
                {
                    if (itmm["type"] == "Component")
                    {
                        std::cout << ConvertCP1251ToUTF8("Вы не можете использовать компонент!\n");
                    }
                    if (itmm["type"] == "Weapon")
                    {
                        std::cout << ConvertCP1251ToUTF8("Вы не можете использовать оружие, вы можете его только экипировать!\n");
                    }
                    if (itmm["type"] == "Armor")
                    {
                        if (itmm["used"] == true)
                        {
                            std::cout << ConvertCP1251ToUTF8("Вы использовали ")
                                + itmm["name"].get<std::string>()
                                + "\n";
                            std::cout << itmm["description"].get<std::string>()
                                + "\n";
                            std::cout << ConvertCP1251ToUTF8("Вам добавлено ")
                                + std::to_string(itmm["armor"].get<int>())
                                + ConvertCP1251ToUTF8(" единиц брони")
                                + "\n";
                        }
                        else
                        {
                            std::cout << ConvertCP1251ToUTF8("У вас уже полная броня!\n");
                        }
                    }
                    if (itmm["type"] == "Heal")
                    {
                        if (itmm["used"] == true)
                        {
                            std::cout << ConvertCP1251ToUTF8("Вы использовали ")
                                + itmm["name"].get<std::string>()
                                + "\n";
                            std::cout << itmm["description"].get<std::string>()
                                + "\n";
                            std::cout << ConvertCP1251ToUTF8("Вам добавлено ")
                                + std::to_string(itmm["heal"].get<int>())
                                + ConvertCP1251ToUTF8(" единиц здоровья\n");
                        }
                        else
                        {
                            std::cout << ConvertCP1251ToUTF8("У вас уже полное здоровье!\n");
                        }
                    }
                }
            }
            else
            {
                std::cout << ConvertCP1251ToUTF8("У вас нет этого предмета!\n");
            }

            nlohmann::json enemyStep = obj["content"]["enemyStep"].get<nlohmann::json>();

            if (!enemyStep.empty())
            {
                addEnemyAttack(enemyStep);
            }

            nlohmann::json playerDeath = obj["content"]["checkPlayerDeath"].get<nlohmann::json>();

            if (!playerDeath.empty())
            {
                addPlayerDeath(playerDeath);
            }
            return;
        };

    // Усурийск новости подПИсюлька
    parsers["Craft"] = [](const nlohmann::json& obj)
        {
            if (obj["content"]["noItemFound"].get<bool>() == true)
            {
                std::cout << ConvertCP1251ToUTF8("Такой предмет не найден\n");
                return;
            }
            if (obj["content"]["noResources"].get<bool>() == true)
            {
                std::cout << ConvertCP1251ToUTF8("У вас недостаточно ресурсов для крафта\n");
                return;
            }
            if (obj["content"]["noCraftFound"].get<bool>() == true)
            {
                std::cout << ConvertCP1251ToUTF8("У этого предмета нет крафтов\n");
                return;
            }

            std::vector<std::string> losted = obj["content"]["lostedItems"].get<std::vector<std::string>>();

            std::cout << ConvertCP1251ToUTF8("Вы скрафтили предмет ")
                + obj["content"]["craftedItem"].get<std::string>()
                + "\n";

            std::cout << "\n";

            int c = 1;

            std::cout << ConvertCP1251ToUTF8("Потерянные предметы: \n");

            for (auto it : losted)
            {
                std::cout << std::to_string(c) + ". " + it + "\n";
                ++c;
            }
            return;
        };

    // фрг, он едет !!! со скоростьюб которая регулируется
    parsers["ChangeFloor"] = [](const nlohmann::json& obj)
        {
            if (obj["content"]["isPlayerBrokeElevator"].get<bool>() == true)
            {
                std::cout << ConvertCP1251ToUTF8("Вы сломали лифт, вы не сможете сменить этаж пока не почините его\n");
                return;
            }

            if (obj["content"]["isElevatorBroken"].get<bool>() == true)
            {
                std::cout << ConvertCP1251ToUTF8("Вы не можете сменить этаж\n");
                return;
            }

            if (obj["content"]["canChange"].get<bool>() == false)
            {
                std::cout << ConvertCP1251ToUTF8("Вы не можете поменять этаж в этой комнате");
                return;
            }

            if (obj["content"]["canGoUp"].get<bool>() == false)
            {
                std::cout << ConvertCP1251ToUTF8("Вы не можете подняться выше\n");
                return;
            }

            if (obj["content"]["canGoDown"].get<bool>() == false)
            {
                std::cout << ConvertCP1251ToUTF8("Вы не можете опуститься ниже\n");
                return;
            }

            if (obj["content"]["changed"].get<bool>() == true)
            {
                if (obj["content"]["moveType"].get<int>() == 1)
                {
                    std::cout << ConvertCP1251ToUTF8("Вы поднялись на ")
                        + std::to_string(obj["content"]["changedFloor"].get<int>())
                        + ConvertCP1251ToUTF8(" этаж\n");
                }
                else
                {
                    std::cout << ConvertCP1251ToUTF8("Вы опустились на ")
                        + std::to_string(obj["content"]["changedFloor"].get<int>())
                        + ConvertCP1251ToUTF8(" этаж\n");
                }
            }

            return;
        };

    // АВПХАВПХВАЗПВАЫПДЙАЬЦЬЛУЙАДЛЦЙУАДЛЙЦУАЛЦАЬ ДЦЙЬАДЦЬДЬЦЙАМЬЦЙПЬЬ ЦЬАЦДЬ ЦЬ
    parsers["Recipes"] = [](const nlohmann::json& obj)
        {
            std::vector<std::string> recipes = obj["content"]["enableCrafts"].get<std::vector<std::string>>();

            std::cout << ConvertCP1251ToUTF8("Доступные крафты: \n");

            int c = 1;

            for (auto it : recipes)
            {
                std::cout << std::to_string(c) + ". " + it + "\n";
                ++c;
            }
            return;
        };

    parsers["Equip"] = [](const nlohmann::json& obj)
        {
            if (obj["content"]["canEquip"].get<bool>() == false)
            {
                std::cout << ConvertCP1251ToUTF8("Вы не можете экипировать этот предмет\n");
                return;
            }

            if (obj["content"]["equiped"].get<bool>() == false)
            {
                std::cout << ConvertCP1251ToUTF8("Не найден предмет\n");
                return;
            }

            std::cout << ConvertCP1251ToUTF8("Вы экипировали \n");
            std::cout << obj["content"]["wep"].get<std::string>() << "\n";

            return;
        };

    // ЧИСТИ ЧИСТИ ГОВНО БЫСТРЕЕ ЧИСТИ ЫВАЫВАВ
    parsers["RepairExit"] = [](const nlohmann::json& obj)
    {
        if (obj["content"]["canFixThisRoom"].get<bool>() == false)
        {
            std::cout << ConvertCP1251ToUTF8("В этой комнате нечего чинить\n");
            return;
        }
        if (obj["content"]["haveResources"].get<bool>() == false)
        {
            std::cout << ConvertCP1251ToUTF8("У вас недостаточно ресурсов для починки\n");

            std::cout << ConvertCP1251ToUTF8("Вам необходимо: \n");

            nlohmann::json needrepair = obj["content"]["needRes"].get<nlohmann::json>();

            int c = 1;

            for (auto it : needrepair)
            {
                std::cout << std::to_string(c) + ". "
                    + it["name"].get<std::string>()
                    + ConvertCP1251ToUTF8(" (")
                    + std::to_string(it["count"].get<int>())
                    + ConvertCP1251ToUTF8(" штуки)\n");
                ++c;
            }

            return;
        }
        if (obj["content"]["isExitBroken"].get<bool>() == false)
        {
            std::cout << ConvertCP1251ToUTF8("Выход не сломан\n");
            return;
        }

        std::cout << ConvertCP1251ToUTF8("Вы починили выход!\n");
        std::cout << ConvertCP1251ToUTF8("Вы потеряли: \n");

        std::vector<std::string> losteditems = obj["content"]["lostedItems"].get<std::vector<std::string>>();

        int c = 1;

        for (auto it : losteditems)
        {
            std::cout << std::to_string(c) + ". " + it + "\n";
            ++c;
        }
    };

    // игроки в комнате
    parsers["PlayersInRoom"] = [](const nlohmann::json& obj)
    {
        std::vector<std::string> plys = obj["content"]["players"].get<std::vector<std::string>>();

        std::cout << ConvertCP1251ToUTF8("Игроки в этой комнате: \n");

        int c = 1;

        for (auto it : plys)
        {
            std::cout << std::to_string(c) + ". " + it + "\n";
            ++c;
        }
        return;
    };

    // КАЗАХСТАНННННННН АААААААААААААААААА
    parsers["Battle"] = [](const nlohmann::json& obj)
    {
        if (obj["content"]["enemyInBattle"].get<bool>() == true)
        {
            std::cout << obj["content"]["enemyInBattlePlayerName"].get<std::string>()
                + ConvertCP1251ToUTF8(" уже дерётся с этим врагом!\n");
            return;
        }
        if (obj["content"]["startedBattle"].get<bool>() == false)
        {
            std::cout << ConvertCP1251ToUTF8("Этого врага нет в комнате!\n");
            return;
        }

        std::cout << ConvertCP1251ToUTF8("Вы вступили в битву с ")
            + obj["content"]["startedBattleWith"].get<std::string>()
            + "\n";

        //Check death

        nlohmann::json enemyStep = obj["content"]["enemyStep"].get<nlohmann::json>();

        if (!enemyStep.empty())
        {
            addEnemyAttack(enemyStep);
        }

        nlohmann::json playerDeath = obj["content"]["checkPlayerDeath"].get<nlohmann::json>();

        if (!playerDeath.empty())
        {
            addPlayerDeath(playerDeath);
        }

        return;
    };

    // В 
    parsers["Attack"] = [](const nlohmann::json& obj)
    {
        if (obj["content"]["inBattle"].get<bool>() == false)
        {
            std::cout << ConvertCP1251ToUTF8("Вы не в битве!\n");
        }

        if (obj["content"]["wepEquiped"].get<bool>() == false)
        {
            std::cout << ConvertCP1251ToUTF8("У вас не экипировано оружие!\n");
        }
        else if (obj["content"]["inBattle"].get<bool>() == true)
        {
            std::cout << ConvertCP1251ToUTF8("Вы нанесли врагу ")
                + obj["content"]["enemyName"].get<std::string>()
                + ConvertCP1251ToUTF8(" ")
                + std::to_string(obj["content"]["makeDamage"].get<int>())
                + ConvertCP1251ToUTF8(" + )")
                + std::to_string(obj["content"]["skillDamage"].get<int>())
                + ConvertCP1251ToUTF8(" урона (Осталось ")
                + std::to_string(obj["content"]["enemyRemainHealth"].get<int>())
                + ConvertCP1251ToUTF8(" здоровья)\n");
        }

        if (obj["content"]["isEnemyDead"].get<bool>() == true)
        {
            std::cout << ConvertCP1251ToUTF8("Вы победили и получили ")
                + std::to_string(obj["content"]["winExp"].get<int>())
                + ConvertCP1251ToUTF8(" опыта");
                + "\n";

            std::cout << ConvertCP1251ToUTF8("Вы получили с врага предмет ")
                + obj["content"]["itemFromEnemy"].get<std::string>()
                + "\n";
        }

        //Check death

        nlohmann::json enemyStep = obj["content"]["enemyStep"].get<nlohmann::json>();

        if (!enemyStep.empty())
        {
            addEnemyAttack(enemyStep);
        }

        nlohmann::json playerDeath = obj["content"]["checkPlayerDeath"].get<nlohmann::json>();

        if (!playerDeath.empty())
        {
            addPlayerDeath(playerDeath);
        }

        nlohmann::json lvUp = obj["content"]["levelUp"].get<nlohmann::json>();

        if (!lvUp.empty())
        {
            addLevelUp(lvUp);
        }
        return;
    };

    // ..4556.d..d.d44s2fd.sf.sf4
    parsers["Skip"] = [](const nlohmann::json& obj)
    {
        if (obj["content"]["inBattle"].get<bool>() == false)
        {
            std::cout << ConvertCP1251ToUTF8("Вы не в битве\n");
        }
        else
        {
            nlohmann::json enemyStep = obj["content"]["enemyStep"].get<nlohmann::json>();

            if (!enemyStep.empty())
            {
                addEnemyAttack(enemyStep);
            }

            nlohmann::json playerDeath = obj["content"]["checkPlayerDeath"].get<nlohmann::json>();

            if (!playerDeath.empty())
            {
                addPlayerDeath(playerDeath);
            }
        }
        return;
    };


    // unknown
    parsers["unknown"] = [](const nlohmann::json& obj)
    {
        std::cout << ConvertCP1251ToUTF8("Неизвестная команда!\n");
        return;
    };

    // inBattle
    parsers["inBattle"] = [](const nlohmann::json& obj)
    {
        std::cout << ConvertCP1251ToUTF8("Вы не можете использовать эту команду в бою!\n");
        return;
    };

    // BADLOCK 
    parsers["badSyntax"] = [](const nlohmann::json& obj)
    {
        std::cout << ConvertCP1251ToUTF8("Неправильный синтаксис!\n");
        return;
    };

    // Нет такой команды
    parsers["Help"] = [](const nlohmann::json& obj)
    {
        try
        {
            std::vector<nlohmann::json> helpList = obj["content"]["help"].get<std::vector<nlohmann::json>>();

            for (auto it : helpList)
            {
                std::cout << it["name"].get<std::string>()
                    + " - "
                    + it["description"].get<std::string>()
                    + "\n";
            }
        }
        catch (const std::exception& ec)
        {
            std::cout << ec.what() << "\n";
        }
    };

    parsersInitialized = true; // УГйрЭкУсИй 
}

void JsonParser(const nlohmann::json& json) 
{
    std::lock_guard<std::mutex> lock(mtx);

    initFillANSWER();
    try 
    {
        std::string responseType = json["type"];

        if (responseType == "ANSWER") 
        {
            std::string commandType = json["content"]["type"];

            auto it = parsers.find(commandType);
            if (it != parsers.end()) 
            {
                it->second(json);
            }
            else 
            {
                std::cout << ConvertCP1251ToUTF8("Вот это наверное не может найти такой команды -> ") << commandType << "\n";
            }
        }
        else if (responseType == "MAP") 
        {
            map.clear();
            map = json["content"];
        }
        else if (responseType == "SERVER")
        {
            std::cout << "СЕРВЕР: " << json["content"] << "\n";
        }

    }
    catch (const std::exception& e)
    {
        std::cout << ConvertCP1251ToUTF8("Ошибка парсинга JSON: ") << e.what() << "\n";
    }

} 