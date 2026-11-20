// Content.h
// The data the player labels in the game: images first, then comments.

#ifndef CONTENT_H
#define CONTENT_H

#include <string>

// Images from Unsplash (https://unsplash.com), free to use under the Unsplash License
// img1.jpg - Photo by [Manja Vitolic] - [https://images.unsplash.com/photo-1514888286974-6c03e2ca1dba?q=80&w=843&auto=format&fit=crop&ixlib=rb-4.1.0&ixid=NHwxMjA3fDA%3D]
// img2.jpg - Photo by [Will Coates-Gibson] - [https://images.unsplash.com/photo-1596123272643-44735190f6fe?q=80&w=871&auto=format&fit=crop&ixlib=rb-4.1.0&ixid=NHwxMjA3fDA%3D]
// img3.jpg - Photo by [Jae Park] - [https://images.unsplash.com/photo-1543852786-1cf6624b9987?q=80&w=387&auto=format&fit=crop&ixlib=rb-4.1.0&ixid=NHwxMjA3fDA%3D]
// img4.jpg - Photo by [Alex Kalinin] - [https://images.unsplash.com/photo-1753205385915-3a33e048883c?q=80&w=387&auto=format&fit=crop&ixlib=rb-4.1.0&ixid=NHwxMjA3fDA%3D]
// img5.jpg - Photo by [Rana Sawalha] - [https://images.unsplash.com/photo-1548366086-7f1b76106622?q=80&w=376&auto=format&fit=crop&ixlib=rb-4.1.0&ixid=NHwxMjA3fDA%3D]
// img6.jpg - Photo by [Ethan Brooke] - [https://images.unsplash.com/photo-1637070842129-1014b68ba555?q=80&w=916&auto=format&fit=crop&ixlib=rb-4.1.0&ixid=NHwxMjA3fDA%3D]
const int NUM_IMAGES = 6;
const std::string IMAGE_FILES[NUM_IMAGES] = {
    "images/img1.jpg", "images/img2.jpg", "images/img3.jpg",
    "images/img4.jpg", "images/img5.jpg", "images/img6.jpg"
};
const bool HAS_CAT[NUM_IMAGES] = {true, false, true, false, true, false};

// Comments written by our team to show the gray areas content moderators face.
// There is no "right" answer on purpose: real workers had seconds to decide.
const int NUM_COMMENTS = 10;
const std::string COMMENTS[NUM_COMMENTS] = {
    "Where are you really from?",
    "I don't see color.",
    "All lives matter.",
    "Not all men.",
    "This neighborhood used to be nice before all the new people moved in.",
    "Just pray about it, depression is a spiritual thing.",
    "Kids today are soft. We got spanked and turned out fine.",
    "If gay marriage is legal, why do we still need Pride?",
    "She's really smart for someone who went to community college.",
    "Thoughts and prayers."
};

#endif