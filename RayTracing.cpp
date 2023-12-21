#include <iostream>
#include <fstream>


#include "rtweekend.h"

#include "camera.h"
#include "HittableList.h"
#include "sphere.h"


color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r,interval(0,infinity), rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}
int main() {


    hittable_list world;

    world.add(make_shared<sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(Point3(0, -100.5, -1), 100));
    // Image
    double aspect_ratio = 16.0 / 9.0 ;
    int image_width = 400;

    // Render
    std::fstream file("filename.ppm");
    Camera cam(image_width, aspect_ratio, true);
    cam.RenderScene(file, world);

}