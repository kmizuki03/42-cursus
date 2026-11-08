*This project has been created as part of the 42 curriculum by <kmizuki>.*

# NetPractice

## Description

NetPractice is a hands-on introduction to the fundamentals of TCP/IP networking.
The goal of the project is to make a series of non-functioning networks work properly
by configuring the right values for each device.

Through a web-based training interface, you are presented with **10 levels**. Each level
displays a network diagram (hosts, routers, switches and their interfaces) together with
one or more objectives — for example, "host A must be able to communicate with host B".
The network is broken on purpose, and you have to fix it by editing the unshaded fields:
IP addresses, subnet masks and routing entries (default gateways and routes).

By solving these levels you build a practical understanding of how addressing works:
how a subnet mask determines which addresses belong to the same network, how a host
decides whether a destination is local or must be sent to a gateway, and how routers
forward packets between different networks.

## Instructions

### Solving the levels

- **Enter your intranet login** in the field on the welcome page before starting. This
  is required so the configuration matches your own account.
  (You may also use the **Evaluation** tab to generate a random configuration.)
- For each level, modify the editable (unshaded) fields until the network is correct.
- Use **Check again** to verify your configuration.
- Read the **logs at the bottom of the page** to understand failures (e.g. a missing
  gateway, an invalid IP, or a destination that matches no route).
- When a level is solved, a **Next level** button appears.

### Exporting configurations

Before moving on, click **Get my config** to download the configuration of the current
level. You need one exported file **per level** for submission, so export every level
before leaving it.

### Submission

- Submit your work to your Git repository.
- Place **10 exported configuration files (one per level)** at the **root** of the
  repository.
- Double-check the file names before submitting.

> **Defense note:** During evaluation you must successfully complete **three random
> levels** within a limited time. External tools are not allowed; only a simple
> calculator such as `bc` is tolerated.

## Resources

### Networking concepts studied

This project relies on the following TCP/IP and networking concepts:

- **TCP/IP addressing** — IPv4 address structure and the network/host split
- **Subnet masks** — how the mask separates the network portion from the host portion,
  and how to compute network/broadcast/usable addresses
- **Default gateways** — how a host reaches networks other than its own
- **Routers and switches** — the difference between layer-2 forwarding and layer-3
  routing, and the role of routing tables
- **OSI layers** — where addressing, switching and routing fit in the model

### References

- IETF RFC 791 — Internet Protocol (IPv4)
- IETF RFC 1918 — Address Allocation for Private Internets
- Cloudflare Learning Center — "What is a subnet mask?" / "What is a router?"
- Subnet / CIDR calculators and cheat sheets (for practice and verification)

### Use of AI

AI was used as a learning and review aid, not as a substitute for understanding:

- To explain concepts such as subnet masks, gateways and routing in plain terms, and to
  check my own reasoning when a level failed.
- To help structure and proofread this `README.md`.
