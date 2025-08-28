 package_name = 'examus2'
 
 ignore = [
  'releases',
  'utils',
 ]
 
 OptionParser.new do |opt|
 files.reject! do |f|
   ignore.any?{ |i| f.start_with?i }
 end
files += ['.htaccess']
 
 code_pattern = Regexp.new old_name, Regexp::IGNORECASE
 code_renames = {