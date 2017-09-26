#include <igl/readOFF.h>
#include <igl/viewer/Viewer.h>

Eigen::MatrixXd V;
Eigen::MatrixXi F;

int main(int argc, char **argv)
{
  // Load the mesh in OFF format
  igl::readOFF(argv[1], V, F);

  // Plot the mesh
  igl::viewer::Viewer viewer;
  viewer.data.set_mesh(V, F);
  viewer.launch();
}
