svm_sources = [
  'svm.c',
  'class.c',
  'log.c',
  'class_file.c',
  'constant_pool.c',
]

svm_export_headers = [
  '../include/svm_attribute_info.h',
  '../include/svm_class.h',
  '../include/svm_class_file.h',
  '../include/svm_const.h',
  '../include/svm_constant_pool.h',
  '../include/svm_field_info.h',
  '../include/svm_globals.h',
  '../include/svm_method_info.h',
  '../include/svm_log.h',
]

svm_args = [
  '-DLOG_USE_COLOR',
  '-pedantic',
  '-std=c99'
]

svm_incdirs = include_directories('../include')

svm_lib = library('svm', svm_sources,
  install : true,
  include_directories : svm_incdirs,
  c_args : svm_args)

foreach header : svm_export_headers
  install_headers(header)
endforeach

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : svm_lib,
                 version : '0.1',
                 name : 'libsvm',
                 filebase : 'svm',
                 description : 'A lightweight embeddable JVM.')

