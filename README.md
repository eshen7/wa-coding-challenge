This is my submission for the coding challenge for the perception team in Wisconsin Autonomous. My method was to convert the image to hsv, detect red objects and find their contours, find the center of each contour, separate them into left and right, and then fit and draw a line through each line of points. I had some trouble finding thresholds that were accurate enough to detect all of the cones and not any of the other surrounding objects but I figured it out after playing with the numbers for a while. I used OpenCV.
![answer](https://github.com/user-attachments/assets/440eb0b1-c20f-4d5e-bfab-29c7f92f412a)
![squirrel](https://github.com/user-attachments/assets/eeec9d8c-80c9-4bd1-a523-5b0d3997efe6)
