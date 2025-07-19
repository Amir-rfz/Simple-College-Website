AP HTTP
===

[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/AP-ECE-UT/APHTTP/license.md)
[![Release](https://img.shields.io/github/release/AP-ECE-UT/APHTTP.svg?color=brightgreen)](https://github.com/AP-ECE-UT/APHTTP/releases/latest)
[![Wiki](https://img.shields.io/badge/GitHub-Wiki-red.svg)](https://github.com/AP-ECE-UT/APHTTP/wiki)

## Introduction

**Simple College Website** is a lightweight C++ web application server and framework that lets students enroll in courses, professors manage courses, and all users maintain their profiles and personal blogs. It is built on simplified versions of [W++](http://konteck.github.io/wpp/), [HappyHTTP](http://scumways.com/happyhttp/happyhttp.html), and [cpp-netlib](http://cpp-netlib.org/).

## Features

- **Student portal**: Browse and enroll in courses.  
- **Professor portal**: Create, update, and delete courses.  
- **User profiles**: Edit personal information, upload avatars.  
- **Blog system**: Users can create, edit, and delete blog posts.  
- **REST‑style HTTP server**: Built-in blocking C++ HTTP framework.

## Prerequisites

- A modern C++ compiler (GCC 9.0+ or Clang 10.0+).  
- CMake ≥ 3.10  
- POSIX‑compatible OS (Linux/macOS).  
- Ports: you’ll need an available TCP port (e.g., 8080).

## Installation

1. **Clone the repo**  
   ```bash
   git clone https://github.com/AP-ECE-UT/APHTTP.git
   cd APHTTP


2. **Make**

   ```bash
   make clean
   make
   ```

   This will produce the server binary `utms.out` in the `build/` directory.

## Running the Application

From the project root (or your `build/` directory), run:

```bash
./utms.out <majors.csv> <students.csv> <courses.csv> <professors.csv> <port>
```

* `<majors.csv>` — list of available majors
* `<students.csv>` — student records
* `<courses.csv>` — course catalog
* `<professors.csv>` — professor records
* `<port>` — HTTP port to listen on

**Example:**

```bash
./utms.out Test/majors.csv Test/students.csv Test/courses.csv Test/professors.csv 8080
Server running on port: 8080
```

Navigate to `http://localhost:8080/` in your browser to begin.

## Preview

*Home page (course catalog):*
![Home Page](images/home.png)

*Profile editing:*
![Profile Page](images/profile.png)

*Blog dashboard:*
![Blog Page](images/blog.png)

