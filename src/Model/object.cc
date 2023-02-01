#include "object.h"

namespace sfleta {
void Object::Parsing(std::string filename) {
  InitObjects(filename.data());
  FillObjects(filename.data());
  CreateTransfomMatrix();
}

void Object::InitObjects(const char* filename) {
  FILE* File = fopen(filename, "r");
  unsigned v_row_size = 0;
  unsigned f_size = 0;

  size_t offset_length = 0;
  char* current_line = NULL;
  while (File && getline(&current_line, &offset_length, File) != -1) {
    if (*current_line == 'v' && *(current_line + 1) == ' ') {
      ++v_row_size;
    } else if (*current_line == 'f') {
      ++f_size;
    }
  }

  matrix_ = new Matrix3D;
  polygon_ = new Polygon;
  matrix_->Resize(v_row_size);
  polygon_->Resize(f_size);

  free(current_line);
  fclose(File);
}

void Object::FillObjects(const char* filename) {
  FILE* File = fopen(filename, "r");
  size_t offset_length = 0;
  char* current_line = NULL;
  while (File && getline(&current_line, &offset_length, File) != -1) {
    if (*current_line == 'v' && *(current_line + 1) == ' ') {
      matrix_->ParseVLine(current_line + 1);
    } else if (*current_line == 'f') {
      polygon_->ParseFLine(current_line + 1);
    }
  }
  free(current_line);
  fclose(File);
}

void Matrix3D::ParseVLine(char* line) {
  size_t row = GetRowV();
  for (int i = 0; *(line++) != '\n'; i++) {
    vertices_->operator()(row, i) = strtod(line, &line);
  }
  ++row;
  SetRowV(row);
}

void Polygon::ParseFLine(char* line) {
  char* tmp_chars = nullptr;
  for (size_t i = 0; *(line) && *(line++) != '\n';) {
    if (*(line - 1) == '/') {
      (void)strtod(line, &line);
    } else if (isdigit(*line)) {
      if (i == 0) {
        tmp_chars = line;
      }
      polygons_->push_back(strtod(line, &line) - 1);
      if (i > 0) {
        polygons_->push_back(polygons_->back());
      }
      i++;
    }
  }
  polygons_->push_back(strtod(tmp_chars, &tmp_chars) - 1);
}

void Object::CreateTransfomMatrix() {
  double min_x = GetVertexElem(0, 0);
  double max_x = GetVertexElem(0, 0);
  double min_y = GetVertexElem(0, 1);
  double max_y = GetVertexElem(0, 1);

  for (size_t i = 1; i < GetVertexCount(); i++) {
    if (GetVertexElem(i, 0) <= min_x) {
      min_x = GetVertexElem(i, 0);
    } else if (GetVertexElem(i, 0) >= max_x) {
      max_x = GetVertexElem(i, 0);
    }

    if (GetVertexElem(i, 1) <= min_y) {
      min_y = GetVertexElem(i, 1);
    } else if (GetVertexElem(i, 1) >= max_y) {
      max_y = GetVertexElem(i, 1);
    }
  }

  double max_x_len = max_x - min_x;
  double max_y_len = max_y - min_y;

  delete transform_matrix_;
  transform_matrix_ =
      new Matrix4D(MaxNumber(max_x_len, max_y_len), ((max_y + min_y) / 2.0));
}

double Object::MaxNumber(double num1, double num2) {
  return (num1 >= num2) ? num1 : num2;
}

}  // namespace sfleta
