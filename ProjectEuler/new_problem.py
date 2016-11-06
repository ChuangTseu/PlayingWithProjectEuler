
import xml.etree.ElementTree as ET

import sys
import re
import argparse
import os

from typing import List, Dict, Any

### CONFIG ###
vcxproj_filename = 'ProjectEuler.vcxproj'
### END CONFIG ###

parser = argparse.ArgumentParser(description='Setup a new problem.')
parser.add_argument('-p', type=int, help='The problem number to be set up.', required=True)

args = parser.parse_args()

new_problem_id = args.p
assert new_problem_id > 0 and new_problem_id < 999999

new_problem_filename = "problem{}.cpp".format(new_problem_id)

ET.register_namespace("", "http://schemas.microsoft.com/developer/msbuild/2003")

tree = ET.parse(vcxproj_filename)

parent_map = {c:p for p in tree.iter() for c in p}

print(tree)

root = tree.getroot()

ns = {'msbuild2003': 'http://schemas.microsoft.com/developer/msbuild/2003'}

problem_elem_dict = {} # type: Dict[int, Any]

cpp_group_elem = None

for cl_compile in root.findall("msbuild2003:ItemGroup/msbuild2003:ClCompile", ns):
    if cpp_group_elem is None:
        cpp_group_elem = parent_map[cl_compile]
    else:
        assert cpp_group_elem == parent_map[cl_compile]

    filename = cl_compile.get("Include")

    match_group = re.match(r"problem(\d+)\.cpp", filename)

    if match_group is None:
        continue

    problem_id = int(match_group.group(1))
    problem_elem_dict[problem_id] = cl_compile

    #print("Found file {} for problem n° {}".format(filename, problem_id))

#print(problem_elem_dict)

if new_problem_id in problem_elem_dict:
    print("The problem n° {} is already present in the Visual Studio project. Abort.".format(new_problem_id))
    sys.exit(0)

if os.path.isfile(new_problem_filename):
    print("The file {} for the problem n° {} already exists. Abort.".format(new_problem_filename, new_problem_id))
    sys.exit(0)


with open("problem.cpp.template", 'r') as template_file:
    with open(new_problem_filename, 'w', newline='\n') as target_file:
        template_cpp_problem = template_file.read()

        problem_main_fn_name = "problem{}".format(new_problem_id)

        #print(template_cpp_problem)

        # __pytemplate__problem_main_fn=problem_main_fn_name
        cpp_problem_full_src = template_cpp_problem.format(__pytemplate__problem_id=new_problem_id)

        #print(cpp_problem_full_src)

        target_file.write(cpp_problem_full_src)
        
        ET.SubElement(cpp_group_elem, "ClCompile", Include=new_problem_filename)

tree.write(vcxproj_filename, xml_declaration=True, encoding='utf-8')