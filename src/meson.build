sources = [
  'svm.c',
  'class.c',
  'log.c',
  'class_file.c',
  'constant_pool.c',
]

args = [
  '-DLOG_USE_COLOR',
  '-pedantic',
  '-Werror',
  '-std=c99'
]

incdirs = include_directories('../include')

exe = executable('svm', sources,
  install : true,
  include_directories : incdirs,
  c_args : args)

