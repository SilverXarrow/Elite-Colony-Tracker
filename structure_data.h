#ifndef STRUCTURE_DATA_H
#define STRUCTURE_DATA_H

#include <Windows.h>

#define NUM_STRUCTURES 10 // Use #define for constant expressions

/**
 * @brief Represents a structure with tier, category, name, and materials.
 */
typedef struct {
    int tier;                  ///< The tier of the structure
    int category;              ///< The category of the structure
    const char* name;          ///< The name of the structure
    const char* materials[3];  ///< The materials of the structure
} Structure;

extern Structure structures[NUM_STRUCTURES]; // External declaration of structures array

/**
 * @brief Displays the materials of a structure in a list box.
 *
 * @param hWnd Handle to the list box window.
 * @param index Index of the structure in the structures array.
 */
void DisplayMaterials(HWND hWnd, int index);

/**
 * @brief Updates the remaining materials of a structure.
 *
 * @param index Index of the structure in the structures array.
 */
void UpdateRemainingMaterials(int index);

#endif // STRUCTURE_DATA_H
