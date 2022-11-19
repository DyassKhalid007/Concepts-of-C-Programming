#include "vm.h"

#include <iostream>
#include <limits>

#include "util.h"


namespace vm {


auto ele_pop = [](vm_state &state){

    if (state.stack.size()==0){
        throw vm_stackfail{"Stack failed"};

    }

    state.stack.pop();
};

auto first_top = [](vm_state &state){


    if (state.stack.size()==0){
        throw vm_stackfail{"Stack failed"};
    }


    auto top_ele = state.stack.top();
    return top_ele;
       
        
       
    };

    auto second_top = [](vm_state & state){


        auto top = first_top(state);

        state.stack.pop();



        auto second =first_top(state);

        state.stack.emplace(top);

        return second;

        
        
    };

vm_state create_vm(bool debug) {
    vm_state state;

    // enable vm debugging
    state.debug = debug;




    


    

    



    register_instruction(state, "PRINT", [&](vm_state& vmstate, const item_t /*arg*/) {
        std::cout << first_top(vmstate) << std::endl;
        return true;
    });


    register_instruction(state, "LOAD_CONST", [](vm_state& vmstate, const item_t value) {
        
        vmstate.stack.emplace(value);
        return true;
    });

    register_instruction(state, "ADD",[&](vm_state& vmstate,const item_t) {


        item_t top = first_top(vmstate);
        item_t s_top = second_top(vmstate);
        vmstate.stack.emplace(top+s_top);
        return true;
    });


    register_instruction(state, "DIV",[&](vm_state& vmstate,const item_t) {


        item_t top = first_top(vmstate);
        item_t s_top = second_top(vmstate);

        if(top==0){

            throw div_by_zero{"Div by 0"};
        }
        
        auto result = s_top/top;
        vmstate.stack.emplace(result);
        return true;
    });
    register_instruction(state, "EQ",[&](vm_state& vmstate,const item_t) {


        item_t top = first_top(vmstate);
        item_t s_top = second_top(vmstate);

        item_t result = top==s_top; 
        vmstate.stack.emplace(result);
        return true;
    });

    register_instruction(state, "NEQ",[&](vm_state& vmstate,const item_t) {


        item_t top = first_top(vmstate);
        item_t s_top = second_top(vmstate);

        item_t result = !(top==s_top); 
        vmstate.stack.emplace(result);
        return true;
    });

    register_instruction(state, "DUP",[&](vm_state& vmstate,const item_t) {


        item_t top = first_top(vmstate); 
        vmstate.stack.emplace(top);
        return true;
    });

    register_instruction(state, "EXIT",[](vm_state& vmstate,const item_t) {


        item_t top = first_top(vmstate); 
        return false;
    });

    register_instruction(state, "POP",[](vm_state& vmstate,const item_t) {

        ele_pop(vmstate);
        return true;
    });

    register_instruction(state, "WRITE",[&](vm_state& vmstate,const item_t) {

        auto top = first_top(vmstate);

        vmstate.result+=std::to_string(top);
        return true;
    });


    register_instruction(state, "WRITE_CHAR",[&](vm_state& vmstate,const item_t) {

        auto top = static_cast<char>(first_top(vmstate));
        vmstate.result+=top;
        return true;
    });


    register_instruction(state, "JMP",[](vm_state& vmstate,const item_t ins_code) {

        vmstate.pc = ins_code;
        return true;
    });


    register_instruction(state, "JMPZ",[&](vm_state& vmstate,const item_t ins_code) {

        auto top = first_top(vmstate);

        ele_pop(vmstate);


        if(top==0){
            vmstate.pc = ins_code;
            
        }
        return true;
    });


    


    


    // TODO create instructions

    return state;
}


void register_instruction(vm_state& state, std::string_view name,
                          const op_action_t& action) {
    size_t op_id = state.next_op_id;

    // TODO make instruction available to vm

    std::string instrunction_name{name};
    state.instruction_ids.emplace(instrunction_name,op_id);
    state.instruction_names.emplace(op_id,instrunction_name);
    state.instruction_actions.emplace(op_id,action);
    state.next_op_id++;




}


code_t assemble(const vm_state& state, std::string_view input_program) {
    code_t code;

    // convert each line separately
    for (auto& line : util::split(input_program, '\n')) {

        auto line_words = util::split(line, ' ');

        // only support instruction and one argument
        if (line_words.size() >= 3) {
            throw invalid_instruction{std::string{"more than one instruction argument: "} + line};
        }

        // look up instruction id
        auto& op_name = line_words[0];
        auto find_op_id = state.instruction_ids.find(op_name);
        if (find_op_id == std::end(state.instruction_ids)) {
            throw invalid_instruction{std::string{"unknown instruction: "} + op_name};
        }
        op_id_t op_id = find_op_id->second;

        // parse the argument
        item_t argument{0};
        if (line_words.size() == 2) {
            argument = std::stoll(line_words[1]);
        }

        // and save the instruction to the code store
        code.emplace_back(op_id, argument);
    }

    return code;
}


std::tuple<item_t, std::string> run(vm_state& vm, const code_t& code) {
    // to help you debugging the code!
    if (vm.debug) {
        std::cout << "=== running vm ======================" << std::endl;
        std::cout << "disassembly of run code:" << std::endl;
        for (const auto &[op_id, arg] : code) {
            if (not vm.instruction_names.contains(op_id)) {
                std::cout << "could not disassemble - op_id unknown..." << std::endl;
                std::cout << "turning off debug mode." << std::endl;
                vm.debug = false;
                break;
            }
            std::cout << vm.instruction_names[op_id] << " " << arg << std::endl;
        }
        std::cout << "=== end of disassembly" << std::endl << std::endl;
    }

    // execution loop for the machine
    while (true) {

        auto& [op_id, arg] = code[vm.pc];

        if (vm.debug) {
            std::cout << "-- exec " << vm.instruction_names[op_id] << " arg=" << arg << " at pc=" << vm.pc << std::endl;
        }

        // increase the program counter here so its value can be overwritten
        // by the instruction when it executes!
        vm.pc += 1;

        // TODO execute instruction and stop if the action returns false.

        if(vm.pc>code.size()){
            throw vm_segfault{"Illegal memory requested"};
        }
        auto func = vm.instruction_actions[op_id];

        if (!func(vm,arg)){
            break;
        }
    }

    return {first_top(vm), vm.result}; // TODO: return tuple(exit value, output text)
}


} // namespace vm
