/*
 * LICENSE
 */
// Description
//@author renzo904, blu
//@category exports
//@keybinding
//@menupath Skeleton
//@toolbar Skeleton
import static java.util.Map.entry;

import ghidra.app.analyzers.RelocationTableSynthesizerAnalyzer;
import ghidra.app.script.GhidraScript;
import ghidra.app.services.Analyzer;
import ghidra.app.util.DomainObjectService;
import ghidra.app.util.Option;
import ghidra.app.util.exporter.CoffRelocatableObjectExporter;
import ghidra.app.util.importer.MessageLog;
import ghidra.framework.model.DomainObject;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.symbol.Namespace;
import ghidra.program.model.symbol.Symbol;
import java.io.File;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ExportDelinker extends GhidraScript
{
    @Override protected void run() throws Exception
    {
        // First run the Relocation Table Synthesizer, to pickup any potentially
        // new globals in the reloc table.
        Analyzer analyzer = new RelocationTableSynthesizerAnalyzer();
        analyzer.added(currentProgram, currentProgram.getMemory(), monitor, new MessageLog());

        // Then, export the COFFs.
        CoffRelocatableObjectExporter exporter = new CoffRelocatableObjectExporter();

        List<Option> exporterOptions = exporter.getOptions(new DomainObjectService() {
            @Override public DomainObject getDomainObject()
            {
                return currentProgram;
            }
        });

        // Change the "Leading underscore" option to "Do Nothing", if available
        for (int i = 0; i < exporterOptions.size(); i++)
        {
            Option opt = exporterOptions.get(i);
            Class<?> cls = opt.getValueClass();

            if (cls != null && cls.isEnum() && opt.getName().equals("Leading underscore"))
            {
                Object[] constants = cls.getEnumConstants();
                for (Object c : constants)
                {
                    if (c.toString().equalsIgnoreCase("Do Nothing"))
                    {
                        exporterOptions.set(i, new Option("Leading underscore", c));
                        printf("Set exporter option 'Leading underscore' = Do Nothing\n");
                        break;
                    }
                }
            }
        }

        exporter.setOptions(exporterOptions);

        File inFile = askFile("Config File", "Select");
        File outDir = askDirectory("Output Folder", "Select");

        String configFile = Files.readString(inFile.toPath(), StandardCharsets.UTF_8);
        Iterable<String> iterable = () -> configFile.lines().iterator();
        for (String objDataStr : iterable)
        {
            if (objDataStr.trim().isEmpty())
            {
                continue; // skip blank lines
            }

            List<String> objData = new ArrayList<>(Arrays.asList(objDataStr.split(",")));
            String objClass = objData.remove(0).trim();
            File outFile = new File(outDir, objClass + ".obj");

            AddressSet set = new AddressSet();
            for (String ghidraClassName : objData)
            {
                ghidraClassName = ghidraClassName.trim();
                printf("Handling %s.obj - class %s\n", objClass, ghidraClassName);

                List<String> ghidraClassNameParts = new ArrayList<>(Arrays.asList(ghidraClassName.split("::")));
                if (ghidraClassNameParts.isEmpty())
                {
                    continue;
                }
                String finalPart = ghidraClassNameParts.remove(ghidraClassNameParts.size() - 1);

                Namespace curNs = null;
                for (String nsPart : ghidraClassNameParts)
                {
                    curNs = this.getNamespace(curNs, nsPart);
                }

                Symbol sym = this.getSymbol(finalPart, curNs);
                if (sym == null)
                {
                    printf("Cannot find namespace or function %s, skipping.\n", ghidraClassName);
                    continue;
                }
                if (!(sym.getObject() instanceof Namespace))
                {
                    printf("Symbol %s is not a namespace, skipping.\n", ghidraClassName);
                    continue;
                }

                Namespace ns = (Namespace)sym.getObject();
                set = set.union(ns.getBody());
            }

            if (set.isEmpty())
            {
                printf("No namespaces found for %s.obj, skipping.\n", objClass);
                continue;
            }

            printf("Exporting %s.obj with %d address ranges -> %s\n", objClass, set.getNumAddressRanges(),
                   outFile.getAbsolutePath());

            exporter.export(outFile, currentProgram, set, monitor);

            if (outFile.exists())
            {
                printf("✅ Wrote %s (%d bytes)\n", outFile.getAbsolutePath(), outFile.length());
            }
            else
            {
                printf("⚠️ Exporter did not produce a file for %s.obj\n", objClass);
            }
        }
    }
}
