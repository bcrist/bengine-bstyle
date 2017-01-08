tool 'bstyle' {
   app {
      icon 'icon/bengine-warm.ico',
      rtti,
      custom {
         outputs = 'src/cxx_lexer.cpp',
         inputs = 'meta/cxx_lexer.rl',
         rule = 'ragel',
         command = 'ragel $flags -o $out $in',
         flags = '-s -C -L -G2',
         generator = true,
         restat = true
      },
      link_project {
         'core',
         'core-id-with-names',
         'util',
         'ctable',
         'cli'
      }
   }
}
