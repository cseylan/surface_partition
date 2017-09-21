#include <igl/readOFF.h>
#include <igl/viewer/Viewer.h>

Eigen::MatrixXd V;
Eigen::MatrixXi F;

int main(void)
{
  // Load the mesh in OFF format
  igl::readOFF("/home/caglar/Desktop/surface_partition/syntetic_cube/visualize_cube/syntetic_cube.off", V, F);

  // Plot the mesh
  igl::viewer::Viewer viewer;
  viewer.data.set_mesh(V, F);
  viewer.launch();
}
