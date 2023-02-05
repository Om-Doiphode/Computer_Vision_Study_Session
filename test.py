
import cv2
import numpy as np
from uwimg import *
im = load_image("data/dogsmall.jpg")
a = nn_resize(im, im.w*4, im.h*4)
save_image(a, "dog4x-nn")


# from uwimg import *
# im = load_image("data/dogsmall.jpg")
# a = bilinear_resize(im, im.w*4, im.h*4)
# save_image(a, "dog4x-bl")


im = load_image("data/dog.jpg")
a = nn_resize(im, im.w//7, im.h//7)
save_image(a, "dog7th-bl")


im = load_image("data/dog.jpg")
f = make_box_filter(7)
blur = convolve_image(im, f, 1)
save_image(blur, "dog-box7")


# from uwimg import *
# im = load_image("data/dog.jpg")
# f = make_box_filter(7)
# blur = convolve_image(im, f, 1)
# thumb = nn_resize(blur, blur.w//7, blur.h//7)
# save_image(thumb, "dogthumb")


im = load_image("data/dog.jpg")
f = make_highpass_filter()
blur = convolve_image(im, f, 1)
save_image(blur, "dog-highPassFilter")


im = load_image("data/dog.jpg")
f = make_sharpen_filter()
blur = convolve_image(im, f, 1)
save_image(blur, "dog-sharpenFilter")


im = load_image("data/dog.jpg")
f = make_emboss_filter()
blur = convolve_image(im, f, 1)
save_image(blur, "dog-embossFilter")

im = load_image("data/dog.jpg")
f = make_gaussian_filter(2)
blur = convolve_image(im, f, 1)
save_image(blur, "dog-gauss2")

# # Load the image
# img = cv2.imread('data/dog.jpg')

# # Split the channels
# b, g, r = cv2.split(img)

# # Define the emboss filter
# kernel = np.array([[-2, -1, 0], [-1, 1, 1], [0, 1, 2]])

# # Apply the filter to each channel
# b_emboss = cv2.filter2D(b, -1, kernel)
# g_emboss = cv2.filter2D(g, -1, kernel)
# r_emboss = cv2.filter2D(r, -1, kernel)

# # Merge the channels back together
# img_emboss = cv2.merge([b_emboss, g_emboss, r_emboss])

# # Show the filtered image
# cv2.imshow('Original Image', img)
# cv2.imshow('Emboss Filter', img_emboss)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
im = load_image("data/dog.jpg")
f = make_gaussian_filter(2)
lfreq = convolve_image(im, f, 1)
hfreq = im - lfreq
reconstruct = lfreq + hfreq
save_image(lfreq, "low-frequency")
save_image(hfreq, "high-frequency")
save_image(reconstruct, "reconstruct")

im = load_image("data/dog.jpg")
res = sobel_image(im)
mag = res[0]
feature_normalize(mag)
save_image(mag, "magnitude")
