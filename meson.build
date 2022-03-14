project('svm', 'cpp', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'c_std=c99', 'default_library=both'])

if get_option('enable-docs')
  doxygen = find_program('doxygen', required : true)

  if not doxygen.found()
    error('`doxygen` was not found. You have the `enable-docs` option enabled. You may want to install Doxygen if you want documentation, or turn off documentation support.')
  endif
endif

subdir('src')

