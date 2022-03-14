svm_sources = [
  'svm.c',
  'class_file.c',
  '../shared/log.c',
]

svm_args = [
  '-DLOG_USE_COLOR',
  '-pedantic',
  '-std=c99'
]

svm_incdirs = include_directories('../../include')

svm_lib = executable('svm', svm_sources,
  install : true,
  include_directories : svm_incdirs,
  link_with : libsvm_lib,
  c_args : svm_args)

