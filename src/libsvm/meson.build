libsvm_sources = [
  'class.c',
  'header/constant_pool.c',
  'header/constant_pool_switch.c',
  'header/access_flags.c',
  'header/attributes.c',
  'header/fields.c',
  'header/interface.c',
  'header/magic.c',
  'header/methods.c',
  'header/this_super.c',
  'header/version.c',
  '../shared/log.c',
]

# TODO: Add more headers
libsvm_export_headers = [
  '../../include/libsvm/class.h',
  '../../include/libsvm/log.h',
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

