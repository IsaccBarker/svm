libgvm_sources = [
  'class.c',
  'magic.c',
  'version.c',
  'constant_pool.c',
  '../shared/log.c',
]

libgvm_export_headers = [
  '../../include/gvm_const.h',
  '../../include/gvm_class.h',
  '../../include/gvm_log.h',
]

libgvm_args = [
  '-DLOG_USE_COLOR',
  '-pedantic',
  '-std=c99'
]

libgvm_incdirs = include_directories('../../include')

libgvm_lib = library('gvm', libgvm_sources,
  install : true,
  include_directories : libgvm_incdirs,
  c_args : libgvm_args)

foreach header : libgvm_export_headers
  install_headers(header)
endforeach

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : libgvm_lib,
                 version : '0.1',
                 name : 'libgvm',
                 filebase : 'gvm',
                 description : 'A lightweight embeddable JVM.')

if get_option('enable-docs') and doxygen.found()
  subdir('docs')
endif

