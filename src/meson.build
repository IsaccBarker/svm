svm_sources = [
  'svm.c',
  'file.c',
  'class.c',
  'log.c',
  'class_file.c',
  'constant_pool.c',
]

svm_args = [
  '-DLOG_USE_COLOR',
  '-pedantic',
  '-Os',
  '-ffunction-sections',
  '-fdata-sections',
]

svm_incdirs = include_directories('../include')

exe = executable('svm', svm_sources,
  install : true,
  include_directories : svm_incdirs,
  c_args : svm_args)

