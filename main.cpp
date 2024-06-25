#include "TGAImage.h"
#include <Eigen/Eigen>
#include "rasterizer.h"
#include "model.h"


Model* model =nullptr;
// int main(){
// 	TGAImage myImage (1920,1080,TGAImage::RGB);
// 	TGAColor White (255,255,255,255);
// 	Eigen::Vector2f tri1[3] ={Eigen::Vector2f(100.,700.),Eigen::Vector2f(500.,1000.),Eigen::Vector2f(700.,800.)};
// 	drawTriangle(tri1[0],tri1[1],tri1[2], myImage, White);
// 	drawLine(myImage, tri1[0], tri1[1], White);
// 	myImage.flip_vertically();
// 	myImage.write_tga_file("../output.tga");
// 	return 0;
// }

// int main(int argc, char** argv) { 
//     TGAImage frame(200, 200, TGAImage::RGB); 
//     Eigen::Vector2i pts[3] = {Eigen::Vector2i(10,10), Eigen::Vector2i(100, 30), Eigen::Vector2i(190, 160)}; 
// 	TGAColor Red {255,0,0,255};
//     triangle(pts, frame, Red); 
//     frame.flip_vertically(); // to place the origin in the bottom left corner of the image 
//     frame.write_tga_file("framebuffer.tga");
//     return 0; 
// }

int main(int argc, char** argv){
    if(2 == argc) 
    {
        model =new Model(argv[1]);
    }else {
        model = new Model("../obj/african_head.obj");
        };
    
    TGAImage image(800, 800, TGAImage::RGB);
    Eigen::Vector3f light_dir(0,0,-1);
    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Eigen::Vector2i screen_coords[3];
        Eigen::Vector3f world_coords[3];
        for (int j=0; j<3; j++) {
            Eigen::Vector3f v = model->vert(face[j]);
            screen_coords[j] = Eigen::Vector2i((v[0]+1.)*image.get_width()/2., (v[1]+1.)*image.get_height()/2.);
            world_coords[j]  = v;
        }
        Eigen::Vector3f n = (world_coords[2]-world_coords[0]).cross(world_coords[1]-world_coords[0]);
        n.normalize();
        float intensity = n.dot(light_dir);
        if (intensity>0) {
            TGAColor color = TGAColor(255*intensity, 255*intensity, 255*intensity, 255);
            triangle(screen_coords, image, color);
        }
    }
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
}