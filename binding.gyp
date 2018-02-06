{
  "targets": [
    {
      "target_name": "RoutonRead",
      "sources": [ "src/RoutonRead.cc", "src/Thread.cc" ],
      "include_dirs": [
      'tmp/include',
	  'src'
      ],
      'link_settings': {
        'libraries': [
          '-lSdtapi'
        ],
        'library_dirs': [
          'tmp/lib'
        ]
      },
	  "msbuild_settings": {
			"Link": {
				"ImageHasSafeExceptionHandlers": "false"
			}
		}
    }
  ]
}
