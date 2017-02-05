#include "colors.inc"
  background { color White }
  camera {
    location <10, 0, -7>
    look_at  <4, 3,  3>
  }
  sphere {
    <0, 0, 3>, 2
    texture {
      pigment { color Yellow }
    }
  }
  
  sphere {
    <-1, 7, 9>, 4
    texture {
      pigment { color Red }
    }
  }              

  sphere {
    <11, 21, 32>, 3
    texture {
      pigment { color Blue }
    }
  }    
  
  sphere {
    <4, -2, 8>, 2
    texture {
      pigment { color Green }
    }
  }
  
  light_source { <5, 5, 7> color White}
  light_source { <10, 4, 2> color White}  
  light_source { <7, 0, -1> color White}  
  