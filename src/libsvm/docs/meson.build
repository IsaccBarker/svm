if get_option('enable-docs') and doxygen.found()
  conf_data = configuration_data()
  conf_data.set('DOXYGEN_INPUT', meson.source_root() + '/include')
  conf_data.set('DOXYGEN_OUTPUT', meson.current_build_dir())
  conf_data.set('DOXYGEN_CURRENT', meson.current_source_dir())
  conf_data.set('DOXYGEN_PROJECT_ROOT', meson.source_root())

  headers = []

  foreach header : libsvm_export_headers
    headers += '../' + header
  endforeach

  doxyfile = configure_file(
    input: 'Doxyfile.in',
    output: 'Doxyfile',
    configuration: conf_data
  )

  custom_target('doc',
    build_by_default: true,
    command: [doxygen, doxyfile],
    input: headers,
    output: ['html']
  )
endif

