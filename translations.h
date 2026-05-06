#pragma once

enum Language {
  LANG_EN,  // English
  LANG_PL,  // Polish
  LANG_DE,  // German
  LANG_FR,  // French
  LANG_ES,  // Spanish
  LANG_COUNT
};

Language current_language = LANG_EN;

// Translation strings
const char* get_text(const char* en, const char* pl, const char* de, const char* fr, const char* es) {
  switch(current_language) {
    case LANG_EN: return en;
    case LANG_PL: return pl;
    case LANG_DE: return de;
    case LANG_FR: return fr;
    case LANG_ES: return es;
    default: return en;
  }
}

// Dashboard strings
const char* get_initializing() {
  return get_text("INITIALIZING", "INICJALIZACJA", "WIRD INITIALISIERT", "INITIALISATION", "INICIALIZANDO");
}

const char* get_unit() {
  return get_text("ppm CO₂", "ppm CO₂", "ppm CO₂", "ppm CO₂", "ppm CO₂");
}

const char* get_label_co2() {
  return get_text("CO₂", "CO₂", "CO₂", "CO₂", "CO₂");
}

const char* get_label_temperature() {
  return get_text("TEMP", "TEMP", "TEMP", "TEMP", "TEMP");
}

const char* get_label_humidity() {
  return get_text("HUM", "WILG", "FEUCHT", "HUM", "HUM");
}

const char* get_unknown() {
  return get_text("Unknown", "Nieznane", "Unbekannt", "Inconnu", "Desconocido");
}

// CO2 Level translations — for display (localized)
const char* get_co2_level_text(CO2LevelType level_type) {
  switch(level_type) {
    case CO2_PERFECT:
      return get_text("Perfect", "Doskonałe", "Perfekt", "Parfait", "Perfecto");
    case CO2_EXCELLENT:
      return get_text("Excellent", "Doskonałe", "Ausgezeichnet", "Excellent", "Excelente");
    case CO2_MODERATE:
      return get_text("Moderate", "Umiarkowane", "Moderat", "Modéré", "Moderado");
    case CO2_POOR:
      return get_text("Poor", "Słabe", "Schlecht", "Mauvais", "Malo");
    case CO2_VERY_POOR:
      return get_text("Very Poor", "Bardzo słabe", "Sehr schlecht", "Très mauvais", "Muy malo");
    case CO2_UNKNOWN:
    default:
      return get_text("Unknown", "Nieznane", "Unbekannt", "Inconnu", "Desconocido");
  }
}

// English-only version for Home Assistant text sensors (not localized)
const char* get_co2_level_text_en(CO2LevelType level_type) {
  switch(level_type) {
    case CO2_PERFECT:   return "Perfect";
    case CO2_EXCELLENT: return "Excellent";
    case CO2_MODERATE:  return "Moderate";
    case CO2_POOR:      return "Poor";
    case CO2_VERY_POOR: return "Very Poor";
    case CO2_UNKNOWN:
    default:            return "Unknown";
  }
}

const char* get_language_name(int lang_index) {
  switch(lang_index) {
    case LANG_EN: return "English";
    case LANG_PL: return "Polski";
    case LANG_DE: return "Deutsch";
    case LANG_FR: return "Français";
    case LANG_ES: return "Español";
    default: return "English";
  }
}
