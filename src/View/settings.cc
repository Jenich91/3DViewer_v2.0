#include "settings.h"

namespace s21 {
void Settings::SaveInFile(SettingStruct settings_struct) {
  QSettings file_settings(filesettings, QSettings::IniFormat);
  file_settings.setValue("IsCentral_projection",
                         settings_struct.IsCentral_projection);
  file_settings.setValue("EdgesWidth", settings_struct.EdgesWidth);
  file_settings.setValue("VertexWidth", settings_struct.VertexWidth);
  file_settings.setValue("VertexType", settings_struct.VertexType);
  file_settings.setValue("IsLineType1", settings_struct.IsLineType1);
  file_settings.setValue("IsPicType1", settings_struct.IsPicType1);

  file_settings.setValue("LineColorX", settings_struct.LineColor.x());
  file_settings.setValue("LineColorY", settings_struct.LineColor.y());
  file_settings.setValue("LineColorZ", settings_struct.LineColor.z());
  file_settings.setValue("LineColorW", settings_struct.LineColor.w());

  file_settings.setValue("BackgroundColorX",
                         settings_struct.BackgroundColor.x());
  file_settings.setValue("BackgroundColorY",
                         settings_struct.BackgroundColor.y());
  file_settings.setValue("BackgroundColorZ",
                         settings_struct.BackgroundColor.z());
  file_settings.setValue("BackgroundColorA",
                         settings_struct.BackgroundColor.w());

  file_settings.setValue("VertexColorX", settings_struct.VertexColor.x());
  file_settings.setValue("VertexColorY", settings_struct.VertexColor.y());
  file_settings.setValue("VertexColorZ", settings_struct.VertexColor.z());
  file_settings.setValue("VertexColorW", settings_struct.VertexColor.w());
}

SettingStruct Settings::LoadFromFile() {
  SettingStruct settings_struct;
  QSettings settings(filesettings, QSettings::IniFormat);
  settings_struct.IsCentral_projection =
      settings.value("IsCentral_projection", "").toBool();
  settings_struct.EdgesWidth = settings.value("EdgesWidth", "").toUInt();
  settings_struct.VertexWidth = settings.value("VertexWidth", "").toUInt();
  settings_struct.VertexType = settings.value("VertexType", "").toUInt();
  settings_struct.IsLineType1 = settings.value("IsLineType1", "").toBool();
  settings_struct.IsPicType1 = settings.value("IsPicType1", "").toBool();

  settings_struct.LineColor.setX(settings.value("LineColorX", "").toDouble());
  settings_struct.LineColor.setY(settings.value("LineColorY", "").toDouble());
  settings_struct.LineColor.setZ(settings.value("LineColorZ", "").toDouble());
  settings_struct.LineColor.setW(settings.value("LineColorW", "").toDouble());

  settings_struct.BackgroundColor.setX(
      settings.value("BackgroundColorX", "").toDouble());
  settings_struct.BackgroundColor.setY(
      settings.value("BackgroundColorY", "").toDouble());
  settings_struct.BackgroundColor.setZ(
      settings.value("BackgroundColorZ", "").toDouble());
  settings_struct.BackgroundColor.setW(
      settings.value("BackgroundColorW", "").toDouble());

  settings_struct.VertexColor.setX(
      settings.value("VertexColorX", "").toDouble());
  settings_struct.VertexColor.setY(
      settings.value("VertexColorY", "").toDouble());
  settings_struct.VertexColor.setZ(
      settings.value("VertexColorZ", "").toDouble());
  settings_struct.VertexColor.setW(
      settings.value("VertexColorW", "").toDouble());
  return settings_struct;
}
}  // namespace s21
