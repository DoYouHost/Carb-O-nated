#pragma once

#include "air_quality_levels.h"

// Translations — shared across all Carb-O-nated variants.

enum Language { LANG_EN, LANG_PL, LANG_DE, LANG_FR, LANG_ES, LANG_COUNT };
Language current_language = LANG_EN;

inline const char* get_text(const char* en, const char* pl, const char* de, const char* fr, const char* es) {
  switch (current_language) {
    case LANG_EN: return en;
    case LANG_PL: return pl;
    case LANG_DE: return de;
    case LANG_FR: return fr;
    case LANG_ES: return es;
    default:      return en;
  }
}

// ── Common ────────────────────────────────────────────────────────────────────
inline const char* get_initializing()      { return get_text("INITIALIZING",       "INICJALIZACJA",                    "INITIALISIERUNG",        "INITIALISATION",              "INICIALIZANDO");      }
inline const char* get_warming_up()        { return get_text("Warming up sensors",  "Rozgrzewanie czujnik\xc3\xb3w",    "Sensoren aufw\xc3\xa4rmen", "Pr\xc3\xa9""chauffage capteurs", "Calentando sensores"); }

// ── Sensor labels ─────────────────────────────────────────────────────────────
inline const char* get_label_co2()         { return get_text("CO2",       "CO2",                          "CO2",               "CO2",                 "CO2");       }
inline const char* get_label_co()          { return get_text("CO",        "CO",                           "CO",                "CO",                  "CO");        }
inline const char* get_label_temperature() { return get_text("Temp",      "Temp",                         "Temp",              "Temp",                "Temp");      }
inline const char* get_label_humidity()    { return get_text("Humidity",  "Wilgotno\xc5\x9b\xc4\x87",    "Feuchte",           "Humidit\xc3\xa9",     "Humedad");   }
inline const char* get_label_pm25()        { return get_text("PM2.5",     "PM2.5",                        "PM2.5",             "PM2.5",               "PM2.5");     }
inline const char* get_label_pm10()        { return get_text("PM10",      "PM10",                         "PM10",              "PM10",                "PM10");      }
inline const char* get_label_pm1()         { return get_text("PM1.0",     "PM1.0",                        "PM1.0",             "PM1.0",               "PM1.0");     }
inline const char* get_label_pm4()         { return get_text("PM4.0",     "PM4.0",                        "PM4.0",             "PM4.0",               "PM4.0");     }
inline const char* get_label_voc()         { return get_text("VOC",       "VOC",                          "VOC",               "VOC",                 "VOC");       }
inline const char* get_header_title()      { return get_text("AIR QUALITY", "JAKO\xc5\x9a\xc4\x86 POW.", "LUFTQUALIT\xc3\x84T", "QUALIT\xc3\x89 AIR", "CALIDAD AIRE"); }

// ── Overall AQ banner ─────────────────────────────────────────────────────────
inline const char* get_aq_overall()        { return get_text("OVERALL AIR QUALITY", "OG\xc3\x93LNA JAKO\xc5\x9a\xc4\x86 POWIETRZA", "GESAMTLUFTQUALIT\xc3\x84T", "QUALIT\xc3\x89 GLOBALE DE L'AIR", "CALIDAD GLOBAL DEL AIRE"); }
inline const char* get_aq_good()           { return get_text("GOOD",       "DOBRA",            "GUT",             "BONNE",                "BUENA");     }
inline const char* get_aq_moderate()       { return get_text("MODERATE",   "UMIARKOWANA",      "M\xc3\x84SSIG",   "MOD\xc3\x89R\xc3\x89""E", "MODERADA"); }
inline const char* get_aq_poor()           { return get_text("POOR",       "Z\xc5\x81""A",     "SCHLECHT",        "MAUVAISE",             "MALA");      }
inline const char* get_aq_very_poor()      { return get_text("VERY POOR",  "BARDZO Z\xc5\x81""A", "SEHR SCHLECHT", "TR\xc3\x88S MAUVAISE", "MUY MALA"); }

// English-only label for HA text sensors (language-independent).
inline const char* get_aq_label_en(AirQualityLevelType t) {
  switch (t) {
    case AQ_GOOD:      return "Good";
    case AQ_MODERATE:  return "Moderate";
    case AQ_POOR:      return "Poor";
    case AQ_VERY_POOR: return "Very Poor";
    default:           return "Unknown";
  }
}

// Localized label for display use.
inline const char* get_aq_label(AirQualityLevelType t) {
  switch (t) {
    case AQ_GOOD:      return get_aq_good();
    case AQ_MODERATE:  return get_aq_moderate();
    case AQ_POOR:      return get_aq_poor();
    case AQ_VERY_POOR: return get_aq_very_poor();
    default:           return "---";
  }
}

inline const char* get_language_name(int i) {
  switch (i) {
    case LANG_EN: return "English";
    case LANG_PL: return "Polski";
    case LANG_DE: return "Deutsch";
    case LANG_FR: return "Fran\xc3\xa7""ais";
    case LANG_ES: return "Espa\xc3\xb1""ol";
    default:      return "English";
  }
}
