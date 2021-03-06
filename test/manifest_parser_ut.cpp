#include <fstream>
#include <iostream>
#include <stdexcept>

#include "gtest/gtest.h"
#include "manifest_parser.h"

using namespace ara::exec::parser;

TEST(AraExecParserParseManifest, InvalidExecutionManifestFileExceptionThrown)
{
    const std::string manifest_path{"noexisting_execution_manifest.json"};  // not existing file
    ManifestParser mp{};
    EXPECT_THROW(mp.parse_execution_manifest(manifest_path), std::runtime_error);
}

TEST(AraExecParserParseManifest, InvalidMachineManifestFileExceptionThrown)
{
    const std::string manifest_path{"noexisting_machine_manifest.json"};  // not existing file
    ManifestParser mp{};
    EXPECT_THROW(mp.parse_machine_manifest(manifest_path), std::runtime_error);
}

TEST(AraExecParserParseManifest, EmptyExecutionManifestFileExceptionThrown)
{
    const std::string manifest_path{"../test/manifests/empty_manifest.json"};
    ManifestParser mp{};
    EXPECT_THROW(mp.parse_execution_manifest(manifest_path), std::runtime_error);
}

TEST(AraExecParserParseManifest, EmptyMachineManifestFileExceptionThrown)
{
    const std::string manifest_path{"../test/manifests/empty_manifest.json"};
    ManifestParser mp{};
    EXPECT_THROW(mp.parse_machine_manifest(manifest_path), std::runtime_error);
}

TEST(AraExecParserParseManifest, ExecutionManifestAllKeysUsedSuccess)
{
    const std::string manifest_path{"../test/manifests/execution_manifest_all_keys.json"};

    const std::string manifest_id{"test_app"};
    const std::string option_kind1{"commandLineShortForm"};
    const std::string option_name1{"name"};
    const std::string option_arg1{"as"};
    const std::string function_group{"MachineState"};
    const std::string mode1{"Running"};
    const std::string process_name{"Proc_1"};

    // Prepare expected manifest object
    ExecutionManifest expected_manifest{};
    ExecutionManifest::Process process{};
    ExecutionManifest::Process::StartupConfig config{};
    ExecutionManifest::Process::StartupConfig::StartupOption option{option_kind1, option_name1,
                                                                    option_arg1};
    ExecutionManifest::Process::StartupConfig::MachineInstanceRef mach_inst_ref{function_group,
                                                                                mode1};
    config.startup_options.push_back(option);
    config.machine_instance_refs.push_back(mach_inst_ref);
    process.startup_configs.push_back(config);
    process.name = process_name;
    expected_manifest.processes.push_back(process);
    expected_manifest.manifest_id = manifest_id;

    ManifestParser mp{};
    auto obtained_manifest = mp.parse_execution_manifest(manifest_path);
    ASSERT_EQ(expected_manifest, obtained_manifest);
}

TEST(AraExecParserParseManifest, ExecutionManifestManifestIdMissingSuccess)
{
    const std::string manifest_path{
        "../test/manifests/execution_manifest_missing_manifest_id.json"};

    const std::string option_kind1{"commandLineShortForm"};
    const std::string option_name1{"name"};
    const std::string option_arg1{"as"};
    const std::string function_group{"MachineState"};
    const std::string mode1{"Running"};
    const std::string process_name{"Proc_1"};

    // Prepare expected manifest object
    ExecutionManifest expected_manifest{};
    ExecutionManifest::Process process{};
    ExecutionManifest::Process::StartupConfig config{};
    ExecutionManifest::Process::StartupConfig::StartupOption option{option_kind1, option_name1,
                                                                    option_arg1};
    ExecutionManifest::Process::StartupConfig::MachineInstanceRef mach_inst_ref{function_group,
                                                                                mode1};
    config.startup_options.push_back(option);
    config.machine_instance_refs.push_back(mach_inst_ref);
    process.startup_configs.push_back(config);
    process.name = process_name;
    expected_manifest.processes.push_back(process);

    ManifestParser mp{};
    auto obtained_manifest = mp.parse_execution_manifest(manifest_path);
    ASSERT_EQ(expected_manifest, obtained_manifest);
}

TEST(AraExecParserParseManifest, ExecutionManifestStartupConfigsSectionMissingSuccess)
{
    const std::string manifest_path{
        "../test/manifests/execution_manifest_missing_startup_configs_section.json"};

    const std::string manifest_id{"test_app"};
    const std::string process_name{"Proc_1"};

    // Prepare expected manifest object
    ExecutionManifest expected_manifest{};
    ExecutionManifest::Process process{};
    process.name = process_name;
    expected_manifest.processes.push_back(process);
    expected_manifest.manifest_id = manifest_id;

    ManifestParser mp{};
    auto obtained_manifest = mp.parse_execution_manifest(manifest_path);
    ASSERT_EQ(expected_manifest, obtained_manifest);
}

TEST(AraExecParserParseManifest, ExecutionManifestStartupOptionsSectionMissingSuccess)
{
    const std::string manifest_path{
        "../test/manifests/execution_manifest_missing_startup_options_section.json"};

    const std::string manifest_id{"test_app"};
    const std::string function_group{"MachineState"};
    const std::string mode1{"Running"};
    const std::string process_name{"Proc_1"};

    // Prepare expected manifest object
    ExecutionManifest expected_manifest{};
    ExecutionManifest::Process process{};
    ExecutionManifest::Process::StartupConfig config{};
    ExecutionManifest::Process::StartupConfig::MachineInstanceRef mach_inst_ref{function_group,
                                                                                mode1};
    config.machine_instance_refs.push_back(mach_inst_ref);
    process.startup_configs.push_back(config);
    process.name = process_name;
    expected_manifest.processes.push_back(process);
    expected_manifest.manifest_id = manifest_id;

    ManifestParser mp{};
    auto obtained_manifest = mp.parse_execution_manifest(manifest_path);
    ASSERT_EQ(expected_manifest, obtained_manifest);
}

TEST(AraExecParserParseManifest, ExecutionManifestMachineInstanceRefsSectionMissingSuccess)
{
    const std::string manifest_path{
        "../test/manifests/execution_manifest_missing_machine_instance_refs_section.json"};

    const std::string manifest_id{"test_app"};
    const std::string option_kind1{"commandLineShortForm"};
    const std::string option_name1{"name"};
    const std::string option_arg1{"as"};
    const std::string process_name{"Proc_1"};

    // Prepare expected manifest object
    ExecutionManifest expected_manifest{};
    ExecutionManifest::Process process{};
    ExecutionManifest::Process::StartupConfig config{};
    ExecutionManifest::Process::StartupConfig::StartupOption option{option_kind1, option_name1,
                                                                    option_arg1};
    config.startup_options.push_back(option);
    process.startup_configs.push_back(config);
    process.name = process_name;
    expected_manifest.processes.push_back(process);
    expected_manifest.manifest_id = manifest_id;

    ManifestParser mp{};
    auto obtained_manifest = mp.parse_execution_manifest(manifest_path);
    ASSERT_EQ(expected_manifest, obtained_manifest);
}

TEST(AraExecParserParseManifest, ExecutionManifestProcessNameMissingSuccess)
{
    const std::string manifest_path{
        "../test/manifests/execution_manifest_missing_process_name.json"};

    const std::string manifest_id{"test_app"};
    const std::string option_kind1{"commandLineShortForm"};
    const std::string option_name1{"name"};
    const std::string option_arg1{"as"};
    const std::string function_group{"MachineState"};
    const std::string mode1{"Running"};

    // Prepare expected manifest object
    ExecutionManifest expected_manifest{};
    ExecutionManifest::Process process{};
    ExecutionManifest::Process::StartupConfig config{};
    ExecutionManifest::Process::StartupConfig::StartupOption option{option_kind1, option_name1,
                                                                    option_arg1};
    ExecutionManifest::Process::StartupConfig::MachineInstanceRef mach_inst_ref{function_group,
                                                                                mode1};
    config.startup_options.push_back(option);
    config.machine_instance_refs.push_back(mach_inst_ref);
    process.startup_configs.push_back(config);
    expected_manifest.processes.push_back(process);
    expected_manifest.manifest_id = manifest_id;

    ManifestParser mp{};
    auto obtained_manifest = mp.parse_execution_manifest(manifest_path);
    ASSERT_EQ(expected_manifest, obtained_manifest);
}

TEST(AraExecParserParseManifest, ExecutionManifestProcessSectionMissingSuccess)
{
    const std::string manifest_path{
        "../test/manifests/execution_manifest_missing_process_section.json"};

    const std::string manifest_id{"test_app"};
    // Prepare expected manifest object
    ExecutionManifest expected_manifest{};
    expected_manifest.manifest_id = manifest_id;

    ManifestParser mp{};
    auto obtained_manifest = mp.parse_execution_manifest(manifest_path);
    ASSERT_EQ(expected_manifest, obtained_manifest);
}

TEST(AraExecParserParseManifest, MachineManifestAllKeysUsedSuccess)
{
    const std::string manifest_path{"../test/manifests/machine_manifest_all_keys.json"};

    const std::string manifest_id{"test_machine"};
    const std::string function_group_name{"MachineState"};
    const std::string mode1{"Starting-up"};
    const std::string mode2{"Running"};
    const std::string mode3{"Shuttingdown"};

    // Prepare expected manifest object
    MachineManifest expected_manifest{};
    MachineManifest::ModeDeclarationGroup mdg{};
    mdg.function_group_name = function_group_name;
    mdg.mode_declarations.push_back(MachineManifest::ModeDeclarationGroup::ModeDeclaration{mode1});
    mdg.mode_declarations.push_back(MachineManifest::ModeDeclarationGroup::ModeDeclaration{mode2});
    mdg.mode_declarations.push_back(MachineManifest::ModeDeclarationGroup::ModeDeclaration{mode3});
    expected_manifest.mode_declaration_groups.push_back(mdg);
    expected_manifest.manifest_id = manifest_id;

    ManifestParser mp{};
    auto obtained_manifest = mp.parse_machine_manifest(manifest_path);
    ASSERT_EQ(expected_manifest, obtained_manifest);
}

TEST(AraExecParserParseManifest, MachineManifestManifestIdMissingSuccess)
{
    const std::string manifest_path{"../test/manifests/machine_manifest_missing_manifest_id.json"};

    const std::string function_group_name{"MachineState"};
    const std::string mode1{"Starting-up"};
    const std::string mode2{"Running"};
    const std::string mode3{"Shuttingdown"};

    // Prepare expected manifest object
    MachineManifest expected_manifest{};

    MachineManifest::ModeDeclarationGroup mdg{};
    mdg.function_group_name = function_group_name;
    mdg.mode_declarations.push_back(MachineManifest::ModeDeclarationGroup::ModeDeclaration{mode1});
    mdg.mode_declarations.push_back(MachineManifest::ModeDeclarationGroup::ModeDeclaration{mode2});
    mdg.mode_declarations.push_back(MachineManifest::ModeDeclarationGroup::ModeDeclaration{mode3});
    expected_manifest.mode_declaration_groups.push_back(mdg);

    ManifestParser mp{};
    auto obtained_manifest = mp.parse_machine_manifest(manifest_path);
    ASSERT_EQ(expected_manifest, obtained_manifest);
}

TEST(AraExecParserParseManifest, MachineManifestModeDeclarationGroupSectionMissingSuccess)
{
    const std::string manifest_path{
        "../test/manifests/machine_manifest_missing_mode_declaration_group_section.json"};

    const std::string manifest_id{"test_machine"};

    // Prepare expected manifest object
    MachineManifest expected_manifest{};
    expected_manifest.manifest_id = manifest_id;

    ManifestParser mp{};
    auto obtained_manifest = mp.parse_machine_manifest(manifest_path);
    ASSERT_EQ(expected_manifest, obtained_manifest);
}

TEST(AraExecParserParseManifest, MachineManifestFunctionGroupNameMissingSuccess)
{
    const std::string manifest_path{
        "../test/manifests/machine_manifest_missing_function_group_name.json"};

    const std::string manifest_id{"test_machine"};
    const std::string function_group_name{"MachineState"};
    const std::string mode1{"Starting-up"};
    const std::string mode2{"Running"};
    const std::string mode3{"Shuttingdown"};

    // Prepare expected manifest object
    MachineManifest expected_manifest{};
    expected_manifest.manifest_id = manifest_id;

    MachineManifest::ModeDeclarationGroup mdg{};
    mdg.mode_declarations.push_back(MachineManifest::ModeDeclarationGroup::ModeDeclaration{mode1});
    mdg.mode_declarations.push_back(MachineManifest::ModeDeclarationGroup::ModeDeclaration{mode2});
    mdg.mode_declarations.push_back(MachineManifest::ModeDeclarationGroup::ModeDeclaration{mode3});
    expected_manifest.mode_declaration_groups.push_back(mdg);
    expected_manifest.manifest_id = manifest_id;

    ManifestParser mp{};
    auto obtained_manifest = mp.parse_machine_manifest(manifest_path);
    ASSERT_EQ(expected_manifest, obtained_manifest);
}

TEST(AraExecParserParseManifest, MachineManifestModeDeclarationsSectionMissingSuccess)
{
    const std::string manifest_path{
        "../test/manifests/machine_manifest_missing_mode_declaration_section.json"};

    const std::string manifest_id{"test_machine"};
    const std::string function_group_name{"MachineState"};

    // Prepare expected manifest object
    MachineManifest expected_manifest{};
    expected_manifest.manifest_id = manifest_id;

    MachineManifest::ModeDeclarationGroup mdg{};
    mdg.function_group_name = function_group_name;
    expected_manifest.mode_declaration_groups.push_back(mdg);
    expected_manifest.manifest_id = manifest_id;

    ManifestParser mp{};
    auto obtained_manifest = mp.parse_machine_manifest(manifest_path);
    ASSERT_EQ(expected_manifest, obtained_manifest);
}

TEST(AraExecParserParseManifest, MachineManifestModeMissingSuccess)
{
    const std::string manifest_path{"../test/manifests/machine_manifest_missing_mode.json"};

    const std::string manifest_id{"test_machine"};
    const std::string function_group_name{"MachineState"};

    // Prepare expected manifest object
    MachineManifest expected_manifest{};
    expected_manifest.manifest_id = manifest_id;

    MachineManifest::ModeDeclarationGroup mdg{};
    mdg.function_group_name = function_group_name;
    expected_manifest.mode_declaration_groups.push_back(mdg);
    expected_manifest.manifest_id = manifest_id;

    ManifestParser mp{};
    auto obtained_manifest = mp.parse_machine_manifest(manifest_path);
    ASSERT_EQ(expected_manifest, obtained_manifest);
}
