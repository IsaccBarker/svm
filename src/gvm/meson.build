gvm_sources = [
  'gvm.c',
  'class_file.c',
  '../shared/log.c',
]

gvm_args = [
  '-DLOG_USE_COLOR',
  '-pedantic',
  '-std=c99'
]

gvm_incdirs = include_directories('../../include')

gvm_lib = executable('gvm', gvm_sources,
  install : true,
  include_directories : gvm_incdirs,
  link_with : libgvm_lib,
  c_args : gvm_args)

