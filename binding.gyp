{
  "targets": [
    {
      "target_name": "kociemba",
      "sources": [
        "src/kociemba.c",
        "src/coordcube.c",
        "src/cubiecube.c",
        "src/facecube.c",
        "src/search.c",
        "src/prunetable_helpers.c",
      ],
      "cflags": ["-std=c99", "-O3"],
      "include_dirs": ["src/include"]
    }
  ]
}