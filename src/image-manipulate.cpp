/* Jeroen Ooms (2016)
 * Bindings to vectorized image manipulations.
 * See API: https://www.imagemagick.org/Magick++/STL.html
 */

#include "magick_types.h"
#include <list>

// [[Rcpp::export]]
XPtrImage magick_image_noise( XPtrImage input, int noisetype){
  XPtrImage output = copy(input);
  for_each ( output->begin(), output->end(), Magick::addNoiseImage((Magick::NoiseType) noisetype));
  return output;
}

/*

// [[Rcpp::export]]
XPtrImage magick_image_annotates( XPtrImage image, const std::string text, Rcpp::String bbox, int gravity){
  Magick::annotateImage fun(text, Magick::Geometry(bbox.get_cstring()));
  for_each ( image->begin(), image->end(), fun);
  return image;
}

*/


// [[Rcpp::export]]
XPtrImage magick_image_blur( XPtrImage input, const double radius = 1, const double sigma = 0.5){
  XPtrImage output = copy(input);
  for_each ( output->begin(), output->end(), Magick::blurImage(radius, sigma));
  return output;
}

// [[Rcpp::export]]
XPtrImage magick_image_charcoal( XPtrImage input, const double radius = 1, const double sigma = 0.5){
  XPtrImage output = copy(input);
  for_each ( output->begin(), output->end(), Magick::charcoalImage(radius, sigma));
  return output;
}

// [[Rcpp::export]]
XPtrImage magick_image_chop( XPtrImage input, Rcpp::String geometry){
  XPtrImage output = copy(input);
  for_each ( output->begin(), output->end(), Magick::chopImage(geometry.get_cstring()));
  return output;
}

// [[Rcpp::export]]
XPtrImage magick_image_colorize( XPtrImage input, const size_t opacity, Rcpp::String color){
  XPtrImage output = copy(input);
  for_each ( output->begin(), output->end(), Magick::colorizeImage(opacity, color.get_cstring()));
  return output;
}

// [[Rcpp::export]]
XPtrImage magick_image_delay( XPtrImage input, int delay){
  XPtrImage output = copy(input);
  for_each ( output->begin(), output->end(), Magick::animationDelayImage(delay));
  return output;
}

// [[Rcpp::export]]
XPtrImage magick_image_format( XPtrImage input, Rcpp::String format){
  XPtrImage output = copy(input);
  for_each ( output->begin(), output->end(), Magick::magickImage(format.get_cstring()));
  return output;
}

// [[Rcpp::export]]
XPtrImage magick_image_trim( XPtrImage input){
  XPtrImage output = copy(input);
  for_each ( output->begin(), output->end(), Magick::trimImage());
  return output;
}

// [[Rcpp::export]]
XPtrImage magick_image_composite( XPtrImage input, XPtrImage composite_image, Rcpp::String offset, int op){
  XPtrImage output = copy(input);
  for_each(output->begin(), output->end(), Magick::compositeImage(composite_image->front(),
    Magick::Geometry(offset.get_cstring()), (Magick::CompositeOperator) op));
  return output;
}

// [[Rcpp::export]]
XPtrImage magick_image_contrast( XPtrImage input, size_t sharpen){
  XPtrImage output = copy(input);
  for_each(output->begin(), output->end(), Magick::contrastImage(sharpen));
  return output;
}

// [[Rcpp::export]]
XPtrImage magick_image_background( XPtrImage input, Rcpp::String color){
  XPtrImage output = copy(input);
  for_each (output->begin(), output->end(), Magick::backgroundColorImage(Magick::Color(color.get_cstring())));
  return output;
}

// [[Rcpp::export]]
XPtrImage magick_image_matte( XPtrImage input, bool matte, Rcpp::String color){
  XPtrImage output = copy(input);
  if(strlen(color.get_cstring()))
    for_each ( output->begin(), output->end(), Magick::matteColorImage(color.get_cstring()));
  for_each ( output->begin(), output->end(), Magick::matteImage(matte));
  return output;
}

// [[Rcpp::export]]
XPtrImage magick_image_pen( XPtrImage input, Rcpp::String color){
  XPtrImage output = copy(input);
  if(strlen(color.get_cstring()))
    for_each ( output->begin(), output->end(), Magick::penColorImage(color.get_cstring()));
  return output;
}

// [[Rcpp::export]]
XPtrImage magick_image_crop( XPtrImage input, Rcpp::String geometry){
  XPtrImage output = copy(input);
  const char * geom = geometry.get_cstring();
  if(strlen(geom)){
    for_each (output->begin(), output->end(), Magick::cropImage(geom));
  } else {
    //crop to size of first image
    for_each (output->begin(), output->end(), Magick::cropImage(output->front().size()));
  }
  return output;
}

// [[Rcpp::export]]
XPtrImage magick_image_scale( XPtrImage input, Rcpp::String geometry){
  XPtrImage output = copy(input);
  const char * geom = geometry.get_cstring();
  if(strlen(geom)){
    for_each (output->begin(), output->end(), Magick::scaleImage(geom));
  } else {
    for_each (output->begin(), output->end(), Magick::scaleImage(output->front().size()));
  }
  return output;
}

// [[Rcpp::export]]
XPtrImage magick_image_border( XPtrImage input, Rcpp::String color, Rcpp::String geometry){
  XPtrImage output = copy(input);
  //need to set color before adding the border!
  if(strlen(color.get_cstring()))
    for_each ( output->begin(), output->end(), Magick::borderColorImage(color.get_cstring()));
  if(strlen(geometry.get_cstring()))
    for_each ( output->begin(), output->end(), Magick::borderImage(geometry.get_cstring()));
  return output;
}
