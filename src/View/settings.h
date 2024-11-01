#ifndef S21_SRC_SETTING_H
#define S21_SRC_SETTING_H

#include <QSettings>
#include <QVector4D>

namespace s21 {
struct SettingStruct {
  bool IsCentral_projection;
  bool IsLineType1;
  bool IsPicType1;

  uint EdgesWidth;
  uint VertexWidth;
  uint VertexType;

  QVector4D BackgroundColor;
  QVector4D LineColor;
  QVector4D VertexColor;
};

// Паттерн singleton: гарантирует, что у класса есть только один экземпляр, и
// предоставляет к нему глобальную точку доступа.
class Settings {
 private:
  QString filesettings = SRCDIR "etc/config.ini";

  Settings(){};
  Settings(const Settings &) = delete;
  ;
  Settings &operator=(Settings &) = delete;
  ;

 public:
  static Settings &GetInstance() {
    static Settings instance;
    return instance;
  }
  QString GetfileSettingsPath() { return filesettings; };
  void SaveInFile(SettingStruct settings);
  SettingStruct LoadFromFile();
};
}  // namespace s21
#endif  // S21_SRC_SETTING_H
