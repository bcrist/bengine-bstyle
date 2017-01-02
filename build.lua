tool { name = 'bstyle',
   projects = {
      app {
         icon = 'icon/bengine-warm.ico',
         rtti = true,
         custom = {
            outputs = { 'src/cxx_lexer.cpp' },
            inputs = { 'meta/cxx_lexer.rl' },
            name = 'ragel',
            command = 'ragel $flags -o $out $in',
            flags = '-s -C -L -G2',
            generator = true,
            restat = true
         },
         src = {
            'src/*.cpp'
         },
         libs = {
            'core',
            'core-id-with-names',
            'util',
            'ctable',
            'cli'
         }
      }
   }
}
