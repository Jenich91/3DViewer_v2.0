#include "Model/object.h"
#include "gtest/gtest.h"

#define EPS 1e-7

TEST(object, Parsing1) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  std::vector<std::vector<double>> res2{
      {1.000000, -1.000000, -1.000000}, {1.000000, -1.000000, 1.000000},
      {-1.000000, -1.000000, 1.000000}, {-1.000000, -1.000000, -1.000000},
      {1.000000, 1.000000, -0.999999},  {0.999999, 1.000000, 1.000001},
      {-1.000000, 1.000000, 1.000000},  {-1.000000, 1.000000, -1.000000}};

  for (size_t i = 0; i < res2.size(); i++) {
    for (size_t j = 0; j < res2[i].size(); j++) {
      ASSERT_NEAR(obj.GetVertexElem(i, j), res2[i][j], EPS);
    }
  }
}

TEST(object, Parsing2) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  std::vector<int> res2{1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4,
                        5, 6, 6, 2, 2, 5, 2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0,
                        0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4, 0, 4, 4, 1, 1, 0,
                        1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};

  for (size_t i = 0; i < res2.size(); i++) {
    ASSERT_EQ(obj.GetFacetsElem(i), res2[i]);
  }
}

TEST(object, Parsing3) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  std::vector<std::vector<double>> res = obj.GetTransformMatrix();
  std::vector<std::vector<double>> res2{
      {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 2}};

  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      ASSERT_NEAR(res[i][j], res2[i][j], EPS);
    }
  }
}

TEST(object, Move1) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  obj.Move(10 / 7.0, 0);
  std::vector<std::vector<double>> res = obj.GetTransformMatrix();
  std::vector<std::vector<double>> res2{
      {1, 0, 0, 10 / 7.0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 2}};

  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      ASSERT_NEAR(res[i][j], res2[i][j], EPS);
    }
  }
}

TEST(object, Move2) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  obj.Move(-10 / 7.0, 0);
  std::vector<std::vector<double>> res = obj.GetTransformMatrix();
  std::vector<std::vector<double>> res2{
      {1, 0, 0, -10 / 7.0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 2}};

  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      ASSERT_NEAR(res[i][j], res2[i][j], EPS);
    }
  }
}

TEST(object, Move3) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  obj.Move(10 / 7.0, 1);
  std::vector<std::vector<double>> res = obj.GetTransformMatrix();
  std::vector<std::vector<double>> res2{
      {1, 0, 0, 0}, {0, 1, 0, (10 / 7.0 - 0)}, {0, 0, 1, 0}, {0, 0, 0, 2}};

  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      ASSERT_NEAR(res[i][j], res2[i][j], EPS);
    }
  }
}

TEST(object, Move4) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  obj.Move(-10 / 7.0, 1);
  std::vector<std::vector<double>> res = obj.GetTransformMatrix();
  std::vector<std::vector<double>> res2{
      {1, 0, 0, 0}, {0, 1, 0, (-10 / 7.0 - 0)}, {0, 0, 1, 0}, {0, 0, 0, 2}};

  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      ASSERT_NEAR(res[i][j], res2[i][j], EPS);
    }
  }
}

TEST(object, Move5) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  obj.Move(10 / 7.0, 2);
  std::vector<std::vector<double>> res = obj.GetTransformMatrix();
  std::vector<std::vector<double>> res2{
      {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 10 / 7.0}, {0, 0, 0, 2}};

  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      ASSERT_NEAR(res[i][j], res2[i][j], EPS);
    }
  }
}

TEST(object, Move6) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  obj.Move(-10 / 7.0, 2);
  std::vector<std::vector<double>> res = obj.GetTransformMatrix();
  std::vector<std::vector<double>> res2{
      {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, -10 / 7.0}, {0, 0, 0, 2}};

  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      ASSERT_NEAR(res[i][j], res2[i][j], EPS);
    }
  }
}

TEST(object, scale1) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  obj.Move(10 * 0.01, 3);
  std::vector<std::vector<double>> res = obj.GetTransformMatrix();
  std::vector<std::vector<double>> res2{
      {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 10 * 0.01 * 2}};

  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      ASSERT_NEAR(res[i][j], res2[i][j], EPS);
    }
  }
}

TEST(object, scale2) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  obj.Move(-10 * 0.01, 3);
  std::vector<std::vector<double>> res = obj.GetTransformMatrix();
  std::vector<std::vector<double>> res2{
      {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, -10 * 0.01 * 2}};

  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      ASSERT_NEAR(res[i][j], res2[i][j], EPS);
    }
  }
}

TEST(object, Rotation1) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  obj.Rotation(10 / 57.0, 0);
  std::vector<std::vector<double>> res = obj.GetTransformMatrix();
  std::vector<std::vector<double>> res2{{1, 0, 0, 0},
                                        {0, cos(10 / 57.0), sin(10 / 57.0), 0},
                                        {0, -sin(10 / 57.0), cos(10 / 57.0), 0},
                                        {0, 0, 0, 2}};

  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      ASSERT_NEAR(res[i][j], res2[i][j], EPS);
    }
  }
}

TEST(object, Rotation2) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  obj.Rotation(-10 / 57.0, 0);
  std::vector<std::vector<double>> res = obj.GetTransformMatrix();
  std::vector<std::vector<double>> res2{
      {1, 0, 0, 0},
      {0, cos(-10 / 57.0), sin(-10 / 57.0), 0},
      {0, -sin(-10 / 57.0), cos(-10 / 57.0), 0},
      {0, 0, 0, 2}};

  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      ASSERT_NEAR(res[i][j], res2[i][j], EPS);
    }
  }
}

TEST(object, Rotation3) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  obj.Rotation(10 / 57.0, 1);
  std::vector<std::vector<double>> res = obj.GetTransformMatrix();
  std::vector<std::vector<double>> res2{{cos(10 / 57.0), 0, -sin(10 / 57.0), 0},
                                        {0, 1, 0, 0},
                                        {sin(10 / 57.0), 0, cos(10 / 57.0), 0},
                                        {0, 0, 0, 2}};

  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      ASSERT_NEAR(res[i][j], res2[i][j], EPS);
    }
  }
}

TEST(object, Rotation4) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  obj.Rotation(-10 / 57.0, 1);
  std::vector<std::vector<double>> res = obj.GetTransformMatrix();
  std::vector<std::vector<double>> res2{
      {cos(-10 / 57.0), 0, -sin(-10 / 57.0), 0},
      {0, 1, 0, 0},
      {sin(-10 / 57.0), 0, cos(-10 / 57.0), 0},
      {0, 0, 0, 2}};

  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      ASSERT_NEAR(res[i][j], res2[i][j], EPS);
    }
  }
}

TEST(object, Rotation6) {
  s21::Object obj;
  obj.Parsing("obj_files/cube.obj");
  obj.Rotation(-10 / 57.0, 2);
  std::vector<std::vector<double>> res = obj.GetTransformMatrix();
  std::vector<std::vector<double>> res2{
      {cos(-10 / 57.0), sin(-10 / 57.0), 0, 0},
      {-sin(-10 / 57.0), cos(-10 / 57.0), 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 2}};

  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      ASSERT_NEAR(res[i][j], res2[i][j], EPS);
    }
  }
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
