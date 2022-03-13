libsvm_sources = [
  'class.c',
  'magic.c',
  'version.c',
  '../shared/log.c',
]

libsvm_export_headers = [
  '../../include/svm_const.h',
  '../../include/svm_class.h',
  '../../include/svm_log.h',
]

libsvm_args = [
  '-DLOG_USE_COLOR',
  '-pedantic',
  '-std=c99'
]

libsvm_incdirs = include_directories('../../include')

libsvm_lib = library('svm', libsvm_sources,
  install : true,
  include_directories : libsvm_incdirs,
  c_args : libsvm_args)

foreach header : libsvm_export_headers
  install_headers(header)
endforeach

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : libsvm_lib,
                 version : '0.1',
                 name : 'libsvm',
                 filebase : 'svm',
                 description : 'A lightweight embeddable JVM.')

if get_option('enable-docs') and doxygen.found()
  subdir('docs')
endif

