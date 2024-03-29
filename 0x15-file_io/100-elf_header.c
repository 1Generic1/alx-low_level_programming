#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/types.h>
#include "main.h"

void print_error_and_exit(const char *error_message)
{
    fprintf(stderr, "Error: %s\n", error_message);
    exit(98);
}

void print_elf_header_info(Elf64_Ehdr *elf_header)
{
    	int i;

	
	printf("Magic: ");
    for (i = 0; i < EI_NIDENT; i++)
        printf("%02x ", elf_header->e_ident[i]);
    printf("\n");

    printf("Class: %s\n", elf_header->e_ident[EI_CLASS] == ELFCLASS32 ? "ELF32" : "ELF64");
    printf("Data: %s\n", elf_header->e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little-endian" : "2's complement, big-endian");
    printf("Version: %d\n", elf_header->e_ident[EI_VERSION]);
    printf("OS/ABI: ");
    switch (elf_header->e_ident[EI_OSABI])
    {
        case ELFOSABI_SYSV:
            printf("UNIX System V ABI\n");
            break;
        case ELFOSABI_HPUX:
            printf("HP-UX ABI\n");
            break;
        case ELFOSABI_NETBSD:
            printf("NetBSD ABI\n");
            break;
        case ELFOSABI_LINUX:
            printf("Linux ABI\n");
            break;
        case ELFOSABI_SOLARIS:
            printf("Solaris ABI\n");
            break;
        case ELFOSABI_FREEBSD:
            printf("FreeBSD ABI\n");
            break;
        case ELFOSABI_OPENBSD:
            printf("OpenBSD ABI\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }
    printf("ABI Version: %d\n", elf_header->e_ident[EI_ABIVERSION]);

    printf("Type: ");
    switch (elf_header->e_type)
    {
        case ET_NONE:
            printf("NONE (No file type)\n");
            break;
        case ET_REL:
            printf("REL (Relocatable file)\n");
            break;
        case ET_EXEC:
            printf("EXEC (Executable file)\n");
            break;
        case ET_DYN:
            printf("DYN (Shared object file)\n");
            break;
        case ET_CORE:
            printf("CORE (Core file)\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }

    printf("Entry point address: 0x%lx\n", elf_header->e_entry);
}

int main(int argc, char *argv[])
{
    const char *filename;
	int fd;
	Elf64_Ehdr elf_header;

	if (argc != 2)
    {
        fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
        exit(98);
    }

    filename = argv[1];
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        print_error_and_exit("Cannot open file");
    if (read(fd, &elf_header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr))
        print_error_and_exit("Cannot read ELF header");

    if (lseek(fd, 0, SEEK_SET) == -1)
        print_error_and_exit("Cannot seek to the beginning of the file");

    print_elf_header_info(&elf_header);

    close(fd);

    return 0;
}

