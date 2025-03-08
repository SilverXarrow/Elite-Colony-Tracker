// structure_data.c

#include "structure_data.h"
#include <Windows.h>

#define NUM_MATERIALS 3 // Define constant for the number of materials

Structure structures[NUM_STRUCTURES]; // Declare the structures array

void InitializeStructures() {
    structures[0] = (Structure){1, 0, "Structure 1", {"Material 1", "Material 2", "Material 3"}};
    structures[1] = (Structure){1, 0, "Structure 2", {"Material 1", "Material 2", "Material 3"}};
    structures[2] = (Structure){2, 1, "Structure 3", {"Material 1", "Material 2", "Material 3"}};
    structures[3] = (Structure){2, 1, "Structure 4", {"Material 1", "Material 2", "Material 3"}};
    structures[4] = (Structure){3, 0, "Structure 5", {"Material 1", "Material 2", "Material 3"}};
    structures[5] = (Structure){3, 1, "Structure 6", {"Material 1", "Material 2", "Material 3"}};
    structures[6] = (Structure){1, 1, "Structure 7", {"Material 1", "Material 2", "Material 3"}};
    structures[7] = (Structure){2, 0, "Structure 8", {"Material 1", "Material 2", "Material 3"}};
    structures[8] = (Structure){3, 0, "Structure 9", {"Material 1", "Material 2", "Material 3"}};
    structures[9] = (Structure){3, 1, "Structure 10", {"Material 1", "Material 2", "Material 3"}};
}

/**
 * @brief Displays the materials of a structure in a list box.
 *
 * @param hWnd Handle to the list box window.
 * @param index Index of the structure in the structures array.
 */
void DisplayMaterials(HWND hWnd, int index) {
    if (index < 0 || index >= NUM_STRUCTURES) {
        // Invalid index, handle error
        return;
    }

    if (!IsWindow(hWnd)) {
        // Invalid window handle, handle error
        return;
    }

    SendMessage(hWnd, LB_RESETCONTENT, 0, 0);
    for (int i = 0; i < NUM_MATERIALS; i++) {
        SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)structures[index].materials[i]);
    }
}

/**
 * @brief Updates the remaining materials of a structure.
 *
 * @param index Index of the structure in the structures array.
 */
void UpdateRemainingMaterials(int index) {
    if (index < 0 || index >= NUM_STRUCTURES) {
        // Invalid index, handle error
        return;
    }

    // Implementation of UpdateRemainingMaterials
    // For example, update the materials of the structure at the given index
}
    #ifndef STRUCTURE_DATA_H
    #define STRUCTURE_DATA_H

    #include <Windows.h>

    const int NUM_STRUCTURES = 10; // Use const for constant expressions

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
     * @brief Initializes the structures array.
     */
    void InitializeStructures();

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
