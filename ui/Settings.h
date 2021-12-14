/**
 * @file    Settings.h
 *
 * This file contains various settings and enumerations that you will need to use in the various
 * assignments. The settings are bound to the GUI via static data bindings.
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QColor>
#include "lib/RGBA.h"

// Enumeration values for the Shapes that the user can select in the GUI.
enum ShapeType {
    SHAPE_CUBE,
    SHAPE_CONE,
    SHAPE_SPHERE,
    SHAPE_CYLINDER,
    SHAPE_TORUS,
    SHAPE_SPECIAL_1,
    SHAPE_SPECIAL_2,
    NUM_SHAPE_TYPES
};

/**
 * @struct Settings
 *
 * Stores application settings for the CS123 GUI.
 *
 * You can access all app settings through the "settings" global variable.
 * The settings will be automatically updated when things are changed in the
 * GUI (the reverse is not true however: changing the value of a setting does
 * not update the GUI).
*/
struct Settings {
    // Loads settings from disk, or fills in default values if no saved settings exist.
    void loadSettingsOrDefaults();

    // Saves the current settings to disk.
    void saveSettings();

    // Snow
    float snowRate;
    float snowSize;
    float snowLevel;
    float windiness;

    // Lighting
    float lightIntensity,
          attQuadratic,
          attLinear,
          attConstant,
          ambientIntensity,
          diffuseIntensity,
          specularIntensity,
          shininess;

    QColor lightColor;
    QColor sphereLColor;
    QColor sphereMColor;
    QColor sphereRColor;
};

// The global Settings object, will be initialized by MainWindow
extern Settings settings;

#endif // SETTINGS_H
