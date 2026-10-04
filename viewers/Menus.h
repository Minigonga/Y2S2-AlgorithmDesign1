#include "Printers.h"

/**
 * @file Menus.h
 * @brief Dá print aos menus.
 */

/**
 * @brief Dá print ao menu principal.
 */
void mainMenu();
/**
 * @brief Dá print ao menu de "Basic Service Metrics".
 */
void secondMenu();
/**
 * @brief Dá print ao menu de "Reliability and Sensitivity to Failures".
 */
void thirdMenu();
/**
 * @brief Dá print ao menu do T2.1.
 */
void wsn2_1Menu();

/**
 * @brief Dá print ao menu de dar input à city.
 */
string inputCity();
/**
 * @brief Dá print ao menu de dar input à reservoir.
 */
string inputReservoir();
/**
 * @brief Dá print ao menu de dar input à/s pump station/s.
 */
vector<string> inputPumpStations();
/**
 * @brief Dá print ao menu de dar input à/s pipe/s.
 */
vector<pair<string,string>> inputPipes();
/**
 * @brief Dá print para o utilizador dar input a qualquer coisa e continuar.
 */
void pressAnyCharacterToContinue();
